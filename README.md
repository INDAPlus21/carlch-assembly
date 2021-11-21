# !Basic And Efficient

## Symbols Legend




## Micro Instructions

    Micro instruction are each 8-bit long and will not exceed this size.

| **Instruction** | **Description** |
|:----------------|:---------------|
| `DEPOSIT`       | Pushes 6-bit number to `R_lv` register. |
| `LOAD @?`       | Copy value from `R_lv` to specified register. |
| `UNLD @?`       | Copy value from specified register to `R_lv`. |
| `POP`           | Pop stack value to  `R_lv`. |
| `PUSH`          | Push current value in `R_lv` to stack. |
| `ADD`           | Add values from `R_o0` and `R_o1` and store value to `R_rt`. |
| `SUB`           | Subtract values from `R_o0` and `R_o1` and store value to `R_rt`. |
| `JUMP :0-7`     | Jump to `label` 0..7. |
| `EXT`           | Terminate program. |
| `SKP`           | If the value in `R_a0` and value in `R_a1` is the same, skip one instruction. |
| `PRT`           | Print value currently in `R_lv`. |
| `LABEL`         | Store `pc` to one of 8 labels. |

## Macro Instructions

    Macro instructions are annoted by 'M_' and consist of mutiple micro instructions allowing for more readable code.

| **Instruction**   | **Description** |
|:------------------|:----------------|
| `M_MOVE @a @b`    | Copy value from `@b` to `@a`. |
| `M_LOAD @a :i`    | Set value of `@a` to `:i`. |
| `M_ADD @a @b @c`  | Add value `@b` and `@c` together and store in `@a`. |
| `M_ADDI @a @b :i` | Add value `:i` to `@c` and store in `@a`. |
| `M_SUB @a @b @c`  | Subtract value `@c` from `@b` and store in `@a`. |
| `M_SUBI @a @b :i` | Subtract value `:i` from `@b` and store in `@a`. |
| `M_PUSH @a`       | Push value in `@a` to stack. |
| `M_POP @a`        | Pop value form stack and store in `@a`. |
| `M_LOOP @a @b :i` | When value in `@a` and `@b` is not the same, jump to given `label`. Every time `@b` will be decreased by 1. |
| `M_PRINT @a`      | Print value stored in `@a`. |

## Registers

    There are four registers, all of which can hold 32 bits of 
    data (integers). They are annotated by a so called brädgård (#)

| **Register**  | **Calling number** |
|:--------------|:-------------------|
| `R_0`         | `@0` ***RESERVED*** |
| `R_lv`        | `@1` ***RESERVED*** |
| `R_pc`        | `@2` ***RESERVED*** |
| `R_rt`        | `@3` |
| `R_o0`        | `@4` |
| `R_o1`        | `@5` |
| `R_h0`        | `@6` |
| `R_v0`        | `@7` |
| `R_a0`        | `@8` |
| `R_a1`        | `@9` |
| `R_a2`        | `@10` |
| `R_a3`        | `@11` |
| `R_t0`        | `@12` |
| `R_t1`        | `@13` |
| `R_t2`        | `@14` |
| `R_t3`        | `@15` |
| `R_t4`        | `@16` |
| `R_t5`        | `@17` |
| `R_t6`        | `@18` |
| `R_t7`        | `@19` |
| `R_s0`        | `@20` |
| `R_s1`        | `@21` |
| `R_s2`        | `@22` |
| `R_s3`        | `@23` |
| `R_s4`        | `@24` |
| `R_s5`        | `@25` |
| `R_s6`        | `@26` |
| `R_s7`        | `@27` |
| `R_gp`        | `@28` |
| `R_sp`        | `@29` |
| `R_fp`        | `@30` |
| `R_ra`        | `@21` |