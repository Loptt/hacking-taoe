PROGRAM=$1
CPROGRAM="$PROGRAM.c"

# if [ gcc -g $CPROGRAM -o $PROGRAM ]; then
#     echo "ERROR!!!"
#     exit
# fi

gcc -g $CPROGRAM -o $PROGRAM

sudo chown root:root $PROGRAM
sudo chmod u+s $PROGRAM

echo " "
echo "STARTING PROGRAM"
echo " "

./$PROGRAM
