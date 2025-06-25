#R                  M                             C
#0        1         2         3         4         5         6         7         8         9          
#123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
#------------------------------------------------------------------------------------------
.data 
arr_register:       .space 128                              # vetor de registradores	
arr_stack:          .space 128                              # vetor de pilha: 0x0x7FFF EFFC
arr_text:           .space 128                              # endereco base: 0x0040 0000
arr_data:           .space 128                              # vetor de dados estaticos: 0x1001 0000
immediate:          .word 0                                 # campo immediate            (16 bits)
address:            .space 7                                # campo address              (26 bits)
opcode:             .word 0                                 # campo opcode               (6 bits)
shamt:              .word 0                                 # campo shamt (instruções R) (5 bits)
funct:              .word 0                                 # campo funct (instruções R) (5 bits)
PC:                 .word 0                                 # registrador PC (program counter)
IR:                 .word 0                                 # registrador IR
RS:                 .word 0
RT:                 .word 0

# Gabarito dos tipos de operacao MIPS
# R (register): [Opcode (6)] [Rs(5)] [Rt(5)] [Rd(5)] [Shamt(5)] [Funct(6)]  = 32 bit
# I (imediate): [Opcode (6)] [Rs(5)] [Rt(5)] [ (16) bit immediate value  ]  = 32 bit
# J     (jump): [Opcode (6)] [           (26) bit word address           ]  = 32 bit

.text
.globl main

# Reg:   Funcao 
# $t0:   endereco base do arr_register
# $t1:   indice atual do vetor (0 a 31)
# $t2:   offset (indice * 4)
# $t3:   endereco de arr_register[$t1]
# $t4:   indice fixo 29 (usado para detectar o $sp)
# $t5:   valor de $sp (stack pointer)
# $t6:   endereco do arr_text
# $t7:   endereco do arr_data

main: 

                    lui $t0, 0x1001                         # carregando em $t0 o endereco base do arr_register
                    ori $t0, $t0, 0x0080                    # (mais de 16 bits = lui + ori)
                    li $t1, 0                               # indice inicial do vetor

loop_inicia_registros:
                    bge $t1, 32, final_inicia_registros     # se >= 32, desvia para final -> fim do laco
                    
                    sll  $t2, $t1, 2                        # $t2 = multiplicacao do indice por 4
                    addu $t3, $t0, $t2                      # $t3 = endereco base + offset 
                                                            # possui o endereco de vetor[$t1]
                    li  $t4, 29                             # $t4 = 29 (indice do $sp)
                    beq $t1, $t4, inicializa_stack_pointer	# se $t1(indice) == $t4(29 // index $sp) desvia
                                                            # para "inicializa_stack_pointer"
                    sw $zero, 0($t3)                        # guarda 0 em arr_register[$t3]
                    j next

inicializa_stack_pointer:
                    lui $t5,      0x7FFF                    # atribuindo endereco de $sp em $t6
                    ori $t5, $t5, 0xEFFC                    # atribuindo endereco de $sp em $t6
                    sw  $t5, 0($t3)                         # guarda o valor de $sp no indice 29 do vetor
                    j   next

next:
                    addi $t1, $t1, 1                        # incrementa o indice
                    j loop_inicia_registros                 # retorna para o loop
    
final_inicia_registros:
                    lui $t6,      0x0040                    # atribuindo endereco de arr_text $t6
                    ori $t6, $t6, 0x0000                    # atribuindo endereco de arr_text $t6

                    lui $t7,      0x1001                    # atribuindo endereco de arr_data $t7
                    ori $t7, $t7, 0x0000                    # atribuindo endereco de arr_data $t7