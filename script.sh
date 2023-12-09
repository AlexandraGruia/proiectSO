if test "$#" -ne 1 #Verifică dacă numărul de argumente din linia de comandă ! 1
then
echo "Folosesete scriptul! "
exit 1
fi

contor=0
while read -r linie || test -n "$linie" #citeste linii dintr-un fisier
    do
        rezultat=`echo $linie | grep ^[A-Z] | grep $1 | grep [.]$ | grep -v ",si"` #verfica daca linia incepe cu litera mare, contine primul argument dat la linia de comanda, se termina cu punct si nu contine "si"
        if test -n "$rezultat" #verifica ca variabila sa nu fie goala
        then
            contor=`expr $contor + 1`
        fi
done
echo $contor