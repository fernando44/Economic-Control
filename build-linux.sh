#!bin/bash
echo -e "\n\nCompiling libraries\n"
rm ./dependencies/lib/* -f -r -d
gcc -c ./dependencies/implementations/record.c -o ./dependencies/lib/record.o
gcc -c ./dependencies/implementations/dir_mgmt.c -o ./dependencies/lib/dir_mgmt.o
gcc -c ./dependencies/implementations/date_time.c -o ./dependencies/lib/date_time.o

ar rv ./dependencies/lib/librecord.a ./dependencies/lib/record.o
ar rv ./dependencies/lib/libdir_mgmt.a ./dependencies/lib/dir_mgmt.o
ar rv ./dependencies/lib/libdate_time.a ./dependencies/lib/date_time.o

echo -e "\nCompiling the program \n"
gcc ./mainFile.c -o ./mainFile -L "./dependencies/lib" -I "./dependencies/include" -lrecord -ldir_mgmt -ldate_time -ansi --std=c99 -static
