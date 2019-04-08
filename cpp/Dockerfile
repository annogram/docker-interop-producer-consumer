FROM teeks99/clang-ubuntu

RUN apt update && \
  apt install -y build-essential \
  unzip \
  git \
  ninja-build \
  curl \
  tar

WORKDIR /opt/
RUN curl -L -O https://dl.bintray.com/conan/installers/conan-ubuntu-64_1_6_1.deb && \
  dpkg -i conan-ubuntu-64_1_6_1.deb && \
  rm -f conan-ubuntu-64_1_6_1.deb && \
  git clone https://github.com/Microsoft/vcpkg.git vcpkg && \
  ./vcpkg/bootstrap-vcpkg.sh && \
  update-alternatives --install /usr/bin/vcpkg vcpkg /opt/vcpkg/vcpkg 1

ADD src /usr/src
WORKDIR /usr/src
RUN g++ *.cpp ./hydra/*.cpp -o ../app.o -std=c++14
WORKDIR /usr/
RUN chmod +"x" app.o
CMD ["./app.o"]