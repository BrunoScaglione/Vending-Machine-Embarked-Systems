<h1 align="center">
Vending Machine software in C
</h1>

<p align="center">
    This project is part of the Embarked Systems Course from the department of Mechatronics of the University of São Paulo (USP).
    It is a software for a Vending Machine. The main goals of the project were to translate how a real Vending Machine operates into needs, requirements and
    software specifications, along with following a UML-based software development project plan. 
</p>

## Description

The software developed simulates a Vending Machine and all it's functionalities for a tipical client and management crew. The real interface of the vending machine becomes
your own computer and you can be the custumer or the manager.

### Typical Use Case

The customer inserts the amount of money in coins, picks the product (or cancels the purchase), then the machine
releases the product and the change (or returns the money if canceled).

The manager first authenticates himself by inserting a password, which gives him access to the internal part
of the machine. The manager replaces products and change manually, next he registers the amount of each product and coin replaced in the system.

## Getting Started

### Running in the terminal

```bash
cd bin/Debug
vendingmachine
```

### With CodeBlocks

Open **vendingmachine.cbp** in CodeBlocks as a project. Build and run.

## Project Details

You can check [my report](https://github.com/BrunoScaglione/Vending-Machine-Embarked-Systems/blob/main/Vending_Machine_.pdf) (in Portuguese) for more details on the project.
