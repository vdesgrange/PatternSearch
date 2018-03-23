
<p align="center">
  <h2 align=center>C++ Matrix search pattern exercise</h2>

  <p align="center">
  <b><a href="#installation">Features</a></b>
  |
  <b><a href="#installation">Installation</a></b>
  |
  <b><a href="#contributing">Contributing</a></b>
</p>

## Introduction

C++ program to research pattern of integers into plain text matrice of integers.

## Features

### Report
* Contain application features descriptions (backlogs).
* Sprint Planification.
* Application systems details.
* Algorithms research.
* Selected data structure
* Search algorithms
* Solution class diagram

### Application features
* Encrypt/Decrypt file with AES-256.
* Build generalised suffix tree from plain text matrice.
* Search sequence feature
* Search closest match feature (not implemented)
* Search unordered feature (not implemented)
* Simple CLI

## Installation

*You must have usual C++ compiler (g++, clang).
*You must have Botan crypto library (>= 2.4.x) installed.
*You muse have CppUnit library.

### Mac OS X / Linux

> Put matrix file into : `./application/files` folder.

* Report

```
## compile report
make clean; make;

## access to report : doc/report.pdf
```

* Program

```
## compile program
make clean; make;

## execute program and encrypt file
./bin/main encrypt ./files/matrice.txt myPassword

## execute program
./bin/main ./files/matrice.txt
./bin/main ./files/cipherFile myPassword

## Compile test
make clean; make test

## Execute test
./bin/tester

```
## Contributing

Viviane Desgrange
