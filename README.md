# Compiler_Operators_Analysis
#### C Program that analysis and calculate addition, subtraction,multiplication and division expressions with 1 or more digits. 

Grammar: 

<pre>
E -> T {E1.h = T.val} E1 {Eval = E1.s}
E1 -> +T {E2.h = E1.h + Tval} E2 {E1.s = E2.s}
E1 -> -T {E2.h = E1.h - Tval} E2 {E1.s = E2.s}
E1 -> empty {E1.s = E1.h}

T -> F {T1.h = F.val} T1 {Tval = T1.s}
T1 -> *F {T2.h = T1.h + Fval} T2 {T1.s = T2.s}
T1 -> /F {T2.h = T1.h - Fval} T2 {T1.s = T2.s}
T1 -> empty {T1.s = T1.h}

F -> (E) {Fval = Eval}
F -> D {Fval = Dval}

D -> d {d1val = d} D1 {dval = d1val}
D1 -> d {d1val = d2val = d1val*10 + d} D2 {d1val = d2val}
D1 -> empty
 </pre>
