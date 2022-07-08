FROM ubuntu:latest

RUN apt-get -y update && apt-get install -y

RUN apt-get -y install build-essential qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools

COPY . /home/yaghooli/qtdock

WORKDIR /home/yaghooli/qtdock

RUN qmake -project

RUN sed '8 i QT += core  gui widgets' qtdock.pro > qttmp.pro 

RUN rm qtdock.pro

RUN mv qttmp.pro qtdock.pro

RUN qmake qtdock.pro

RUN make 

ENV DISPLAY=host.docker.internal:0.0

CMD ["./qtdock"]
