#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE TOKENS
#define TK0 0 // vazio
#define TK1 1 // +
#define TK2 2 // -
#define TK3 3 // *
#define TK4 4 // /
#define TK5 5 // d
#define TK6 6 // (
#define TK7 7 // )

// GRAMÁTICA
//E -> T {E1.h = T.val} E1 {Eval = E1.s}
//E1 -> +T {E2.h = E1.h + Tval} E2 {E1.s = E2.s}
//E1 -> -T {E2.h = E1.h - Tval} E2 {E1.s = E2.s}
//E1 -> & {E1.s = E1.h}

//T -> F {T1.h = F.val} T1 {Tval = T1.s}
//T1 -> *F {T2.h = T1.h + Fval} T2 {T1.s = T2.s}
//T1 -> /F {T2.h = T1.h - Fval} T2 {T1.s = T2.s}
//T1 -> & {T1.s = T1.h}

//F -> (E) {Fval = Eval}
//F -> D {Fval = Dval}

//D -> d {d1val = d} D1 {dval = d1val}
//D1 -> d {d1val = d2val = d1val*10 + d} D2 {d1val = d2val}
//D1 -> &


// Variáveis Globais <o>

int tk;
int tklinha = 0;
int tkcoluna = 0;
int pos = 0;
char expression[400] = "(5*20)-86/2";

// <*********** INICIO DO ANALISADOR LÉXICO ***********>

// Implemente aqui seu analisador Léxico

// <*********** FIM DO ANALISADOR LÉXICO ***********>

// Protótipo das Funções do Analisador Sintático

int E(int *eval);

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	
	if(expression[pos] >= '0' && expression[pos] <= '9'){
		tk = TK5;
	}
	else{
		switch(expression[pos]){
			case '+':
				tk = TK1;
				break;
			case '-':
				tk = TK2;
				break;
			case '*':
				tk = TK3;
				break;
			case '/':
				tk = TK4;
				break;
			case '(':
				tk = TK6;
				break;
			case ')':
				tk = TK7;
				break;
			default:
				tk = TK0;
				break;
		}
	}
	pos++;
}

//Implemente aqui a sua função marcaPosToken()

void marcaPosToken() {
}

//Implemente aqui a sua função restauraPosToken()

void restauraPosToken() {
}

//D1 -> d D1 | ? 
int D1(int *d1val){
	int d2val;
	if(tk == TK5){// d
		*d1val = d2val = (*d1val * 10) + (expression[pos-1] - '0');
		getToken();
		if (D1(&d2val)){
			*d1val = d2val;
			return 1;
		}
		else {return 0;}
	}
	else {
		return 1;
	}
	
}

//D -> d D1 
int D(int *dval){
	int d1val;
	if(tk == TK5){// d
		d1val = expression[pos-1] - '0';
		getToken();
		if (D1(&d1val)){
			*dval = d1val;
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//F -> ( E ) | D 
int F(int *fval){
	int eval,dval;
	if(tk == TK6){// (
		getToken();
		if (E(&eval)){
			if(tk == TK7){// )
				getToken();
				*fval = eval;
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else if (D(&dval)){
		*fval = dval;
		return 1;
	}
	else {return 0;}
}

//T1 -> * F T1 | / F T1 | ? 
int T1(int T1h, int *T1s){
	int T2h,T2s,Fval;
	if(tk == TK3){// *
		getToken();
		if (F(&Fval)){
			T2h = T1h * Fval;
			if (T1(T2h,&T2s)){
				*T1s = T2s;
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else if(tk == TK4){// /
		getToken();
		if (F(&Fval)){
			T2h = T1h / Fval;
			if (T1(T2h,&T2s)){
				*T1s = T2s;
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else {
		*T1s = T1h;
		return 1;
	}
}


//T -> F T1	
int T(int *tval){
	int T1h,T1s,Fval;
	//*eval = 12;
	if (F(&Fval)){
		T1h = Fval;
		if (T1(T1h,&T1s)){
			*tval = T1s;
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}


//E1 -> + T E1 | - T E1 | ? 
int E1(int E1h, int *E1s){
	int E2h,E2s,Tval;
	if(tk == TK1){// +
		getToken();
		if (T(&Tval)){
			E2h = E1h + Tval;
			if (E1(E2h,&E2s)){
				*E1s = E2s;
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else if(tk == TK2){// -
		getToken();
		if (T(&Tval)){
			E2h = E1h - Tval;
			if (E1(E2h,&E2s)){
				*E1s = E2s;
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else {
		*E1s = E1h;
		return 1;
	}
}


//E -> T E1 
int E(int *eval){
	int E1h,E1s,Tval;
	//*eval = 12;
	if (T(&Tval)){
		E1h = Tval;
		if (E1(E1h,&E1s)){
			*eval = E1s;
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>

int main(){
	int eval = 0;
	getToken();
	E(&eval);
	printf("Resultado:%d",eval);
}
