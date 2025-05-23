#simulador.asm
#programa para simular um processador MIPS virtual
#buscando, decodificando e executando instruções
#Autores: Miguel Avila de Oliveira e Nicolas Monteiro Longo

#------------------------------------------------------------------------------------------
#régua baseada na que o professor mostrou nos exemplos em aula
#R                  M                             C
#0        1         2         3         4         5         6         7         8         9          
#123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
#------------------------------------------------------------------------------------------

# Gabarito dos tipos de operacao MIPS
# R (register): [Opcode (6)] [Rs(5)] [Rt(5)] [Rd(5)] [Shamt(5)] [Funct(6)]  = 32 bit
# I (imediate): [Opcode (6)] [Rs(5)] [Rt(5)] [ (16) bit immediate value  ]  = 32 bit
# J     (jump): [Opcode (6)] [           (26) bit word address           ]  = 32 bit

.data                                                       # declaração de variáveis
# ------------------------------------- registradores -------------------------------------
arr_register:       .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0x7FFFEFFC, 0, 0   # arr_register[29] = 0x7FFFEFFC
PC:                 .word 0x00400000                        # registrador PC (program counter)
IR:                 .word 0                                 # registrador IR
RS:                 .word 0
RT:                 .word 0
# ---------------------------------------- memória ----------------------------------------
vet_pilha:          .space 5000                             # vetor de pilha: 0x0x7FFF EFFC
vet_instr:          .space 5000                             # endereco base: 0x0040 0000
vet_data:           .space 5000                             # vetor de dados estaticos: 0x1001 0000
# ------------------------------------- campos instr -------------------------------------
address:            .space 7                                # campo address              (26 bits)
immediate:          .word 0                                 # campo immediate            (16 bits)
opcode:             .word 0                                 # campo opcode               (6 bits)
shamt:              .word 0                                 # campo shamt (instruções R) (5 bits)
funct:              .word 0                                 # campo funct (instruções R) (5 bits)
# ---------------------------------------- geral -----------------------------------------
f_instr:            .asciiz "instrucoes.bin"	
f_dados:            .asciiz "dados.dat"
buffer:             .space 1                                # vamos ler byte-a-byte
# -------------------------------------- constantes --------------------------------------
.equ TEXT_BASE_ADDRESS,  0x00400000
.equ DATA_BASE_ADDRESS,  0X10010000
.equ STACK_BASE_ADDRESS, 0x7FFFEFFC

.text
.globl main

_init: 
                    jal main
_finit:
                    move $a0, $v0                           # $a0 = valor de retorno do main
                    li   $v0, 17                            # $v0 = código 17 (exit2)
                    syscall                                 # chamada ao sistema para encerrar o programa

# Reg:   Funcao 
# $t0:   

# operacoes a serem implementadas:
# aritmeticas: add, sub, addi
# logicas: and, or, andi, ori
# transferencia de dados: lw, sw
# desvios: beq, bne, j
# outras: sll, srl, syscall 

main:
                    jal carregar_instrucoes                 # procedimento que carrega os dados do arquivo.bin no vetor                 
                    jal carregar_dados                      # procedimento que carrega os dados do arquivo.dat no vetor
                    
                    # BUSCA
                    # ler o endereço de PC
                    # calcular o indice (offset) com base no pc
                    # ver em vetor_text[indice] qual a instrução a ser realizada
                    # DECODIFICAÇÃO
                    # decodificar os campos da instrução lida
                    # guardar na memoria os campos
                    # ver o que representa a instrução decodificada
                    # EXECUTA
                    # executa a instrução

                    li $v0, 10                              # $v0 = código de chamada do sistema (exit)
                    syscall                                 # realiza a chamada de sistema com os parametros acima



carregar_instrucoes:
# prólogo (alocar pilha + salvar registradores)
                    addi $sp, $sp, -8
                    sw $ra, 4($sp)
                    sw $s0, 0($sp)

                    li $v0, 13                              # $v0 = código de chamada do sistema (abrir arquivo) 
                    la $a0, f_instr                         # $a0 = endereço p/ string com o nome do arquivo 
                    li $a1, 0                               # $a1 = flag de abertura de arquivo (modo leitura)
                    syscall                                 # abre o arquivo
#                                                           # descritor do arquivo está em $v0

                    move $t0, $v0                           # $t0 = descritor do arquivo
#                                                           # é uma boa prática não manter informações nos registradores $ax e $vx

                    la $t1, vet_instr                       # $t1 = endereço do vet_instr
                    jal ler_arquivo

                    move $a0, $t0                           # $a0 = descritor do arquivo
                    li $v0, 16                              # $v0 = fechar arquivo
                    syscall                                 # fecha o arquivo

# epílogo (restaurar registradores e destruir stack frame)
                    lw $ra, 4($sp)
                    lw $s0, 0($sp)
                    addi $sp, $sp, 8

                    jr $ra                                  # return address

carregar_dados:
# prólogo (alocar pilha + salvar registradores)
                    addi $sp, $sp, -8
                    sw $ra, 4($sp)
                    sw $s0, 0($sp)

                    li $v0, 13                              # $v0 = código de chamada do sistema (abrir arquivo) 
                    la $a0, f_dados                         # $a0 = endereço p/ string com o nome do arquivo
                    li $a1, 0                               # $a1 = flag de abertura de arquivo (modo leitura)
                    syscall                                 # abre o arquivo

                    move $t0, $v0                           # $t0 = descritor do arquivo

                    la $t1, vet_data                        # $t1 = endereço do vet_data
                    jal ler_arquivo                         # leitura do arquivo

                    li $v0, 16                              # $v0 = fechar arquivo
                    move $a0, $t0                           # $a0 = descritor do arquivo
                    syscall                                 # fecha o arquivo

############################################################# epílogo (restaurar registradores e destruir stack frame)
                    lw $ra, 4($sp)
                    lw $s0, 0($sp)
                    addi $sp, $sp, 8

                    jr $ra                                  # return address

ler_arquivo:
                    li $t2, 0                               # $t2 = contador de bytes
ler_loop:
                    li $v0, 14                              # $v0 = ler do arquivo
                    move $a0, $t0                           # $a0 = descritor do arquivo
                    la $a1, buffer                          # $a1 = endereço do buffer
                    li $a2, 1                               # $a2 = 1
                    syscall                                 # le arquivo

                    beq $v0, $zero, fim_leitura             # $v0 == 0 -> fim da leitura

                    lb $t3, buffer                          # $t3 = byte lido
                    sb $t3, 0($t1)                          # salva o byte no vetor

                    addi $t1, $t1, 1                        # incrementa endereço do vetor
                    addi $t2, $t2, 1                        # incrementa o contador

                    j ler_loop                              # continua o loop
fim_leitura:
                    jr $ra                                  # retorna para o $ra

# o professor quer que o programa receba um endereço "virtual" de memória que represente uma
# instrução no nosso vetor_instr
# o jeito que eu pensei foi calcular o índice do vetor relativo ao endereço recebido
# a seguinte função recebe um endereço de PC, subtrai o e.b e retorna o índice relativo no array 
endereco_para_offset:
                    addi $sp, $sp, -8                       # aloca o espaço na pilha (para o stack frame)
                    sw $ra, 4($sp)                          # $ra -> salvo na pilha
                    sw $s0, 0($sp)                          # #sp -> salvo na pilha

                    sub $v0, $a0, $a1                       # $v0 = offset (endereço - base)

                    lw $ra, 4($sp)                          # restaura $ra
                    lw $s0, 0($sp)                          # restaura $s0
                    addi $sp, $sp, 8                        # destroi o stack frame
                    jr $ra                                  # retorna para o $ra
