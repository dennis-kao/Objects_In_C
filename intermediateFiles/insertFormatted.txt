#include<stdio.h>
#include<stdlib.h>






struct
 
A
 
{



int
 
a
,

 
b
;




 

 

 
int
 
(

*
Afnif
)

 
(
struct
 
A
 

*

,

 
int
,

 
float
*

)

;




 

 

 
int
 
(

*
Afnifll
)

 
(
struct
 
A
 

*

,

 
int
,

 
float
,

 
long
 
long
)

;




}

;












/* overloaded methods with multiple types */






int
 
Afnif
 
(
struct
 
A
 

*

 
object
,

 
int
 
i
,

 
float
*

 
pj
)

 
{




 

 

 

 

 

 
object->a
 
=
 
i
 

+

 
(
int
)

 

*
pj
;




 

 

 
}

 






int
 
Afnifll
 
(
struct
 
A
 

*

 
object
,

 
int
 
i
,

 
float
 
j
,

 
long
 
long
 
k
)

 
{




 

 

 

 

 

 
object->b
 
=
 
i
 

+

 
(
int
)

 
j
 

+

 
(
int
)

 
k
;




 

 

 
}

 






void
 
ConstructorA
 
(
struct
 
A
*

 
newStruct
)

 
{




	
newStruct
-
>Afnif
 
=
 
&Afnif
;




	
newStruct
-
>Afnifll
 
=
 
&Afnifll
;




}



int
 
main
(
int
 
argc
,

 
char
 

*
argv[]
)

 
{



struct
 
A
 
myA
;



ConstructorA
 
(
&myA
)

;



int
 
vali
;



float
 
valj
;



long
 
long
 
valk
;



float
 

*
pj
;







 

 

 
vali
 
=
 
1
;




 

 

 
valj
 
=
 
2
.
5
;




 

 

 
valk
 
=
 
10
;




 

 

 
pj
 
=
 
&valj
;







 

 

 
myA
.
Afnif
(
&myA
,

 
vali
,
pj
)

;




 

 

 
myA
.
Afnif
(
&myA
,

 
vali
,
valj
,
valk
)

;







 

 

 
if
 
(

(
myA
.
a
 
==
 
3
)

 
&&
 
(
myA
.
b
 
==
 
13
)

)




 

 

 

 

 

 
return
(
0
)

;




 

 

 
else



 

 

 

 

 

 
return
(
1
)

;




}






