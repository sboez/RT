if [ -e ../a.out ]
then
	EXE="$PWD"/../a.out
	echo $EXE
elif [ -e ../rt ]
then
	EXE="$PWD"/../rt
	echo $EXE
elif [ -e ../debug ]
then
	EXE="$PWD"/../debug
	echo $EXE
else
	echo Pas d\'exécutable.
	exit
fi
for map in complex/*$1*.xml
do
	echo "$PWD/$map"
	"$EXE" "$PWD/$map" 128
done
