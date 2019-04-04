FROM teeks99/clang-ubuntu

ADD src /usr/src
WORKDIR /usr/src
RUN g++ *.cpp -o ../app.o
WORKDIR /usr/
RUN chmod +"x" app.o
CMD ["./app.o"]