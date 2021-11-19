# !Basic And Efficient

## Symbols Legend



## Instructions

## Instructions

| **Instruction** | **Operation** | **Description** |
|:----------------|:--------------|:----------------|
| `PUSH`          | `op<7:6> imm<5:0>` | Pushes 6-bit number to stack. |
| `MOP`           | `op<7:6> imm<5:4>` | Calls mathematical operator and operates on last 2 numbers from stack and pushed result |
| `LOAD`          | `op<7:6> reg<5:1> imm<0>` | Load last value from stack to register. |
| `BLE`           | `op<7:6> reg<5:1> imm<0>` | Jump to label if register 0 is less than or equal to given register. |

### Mathematical Instructions

| **Instruction** | **Description** |
|:----------------|:----------------|
| `MOP +`         | Addition. |
| `MOP -`         | Subtraction, order of the operating is most recent stack. |
| `MOP *`         | Multiplication. |
| `MOP /`         | Divsion. |

## Registers

    There are four registers, all of which can hold 32 bits of 
    data (integers). They are annotated by a so called brädgård (#)

    - #0    // always equals 0
    - #1    // handles I/O
    - #2                                    
    - #3