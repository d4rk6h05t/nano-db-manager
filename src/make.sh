rm *.dat 
rm *.o
rm app

g++ -c entity.cc
g++ -c attribute.cc
g++ -c data_dictionary_file.cc
g++ -c view.cc

g++ main.cc -o app entity.o attribute.o data_dictionary_file.o view.o
