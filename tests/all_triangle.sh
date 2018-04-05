if [ -e ../a.out ]
then
	EXE="$PWD"/../a.out
	echo $EXE
elif [ -e ../rt ]
then
	EXE="$PWD"/../rt
	echo $EXE
else
	echo Pas d\'exécutable.
	exit
fi
for map in triangle/*$1*.xml
do
	echo "$PWD/$map"
	"$EXE" "$PWD/$map" 128
done
