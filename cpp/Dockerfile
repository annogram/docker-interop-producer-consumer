FROM teeks99/clang-ubuntu
ADD src /usr/src
WORKDIR /usr/src
RUN g++ *.cpp ./hydra/*.cpp -o ../app.o -std=c++17 -lpthread
WORKDIR /usr/
RUN chmod +"x" app.o
CMD ["./app.o"]