# Animated List

## Compilation
```
g++ AnimatedList.cpp InputGetter.cpp PositionManager.cpp -lglut -lGL -lGLU -lGLEW -std=c++11
```

## Usage
```
./a.out filename
```

## The language

add **element**</br>
delete **index**</br>
highlight **index**</br>
set **index**,**element**

Where **element** is any string and **index** is a positive integer represeting the index of some element in the list.

## Example

```
add 3
add 4
add 5
add 6
highlight 2
set 3,100
highlight 3
```

To see the results, save the above in a file and execute the language using

```
./a.out filename
```
