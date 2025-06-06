#simulador.asm
#programa para simular um processador MIPS virtual
#buscando, decodificando e executando instruÃ§Ãµes
#Autores: Miguel Avila de Oliveira e Nicolas Monteiro Longo

#------------------------------------------------------------------------------------------
#rÃ©gua baseada na que o professor mostrou nos exemplos em aula
#R                  M                             C
#0        1         2         3         4         5         6         7         8         9          
#123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
#------------------------------------------------------------------------------------------

# Gabarito dos tipos de operacao MIPS
# R (register): [Opcode (6)] [Rs(5)] [Rt(5)] [Rd(5)] [Shamt(5)] [Funct(6)]  = 32 bit
# I (imediate): [Opcode (6)] [Rs(5)] [Rt(5)] [ (16) bit immediate value  ]  = 32 bit
# J     (jump): [Opcode (6)] [           (26) bit word address           ]  = 32 bit

#TEXT_BASE_ADDRESS,  0x00400000
#DATA_BASE_ADDRESS,  0X10010000
#STACK_BASE_ADDRESS, 0x7FFFEFFC

.data                                                       # declaraÃ§Ã£o de variÃ¡veis
# ------------------------------------- registradores -------------------------------------
tamanho_codigo:    .word 0                 # Será preenchido com o tamanho real do código
str_fim_sucesso:   .asciiz "\n[Programa executado com sucesso - Todas instruções completas]\n"
str_branch_taken:   .asciiz "\n  Branch TAKEN"
str_fim_execucao:   .asciiz "\n[Execução finalizada pelo simulador]\n"
str_branch_not_taken: .asciiz "\n  Branch NOT taken"
str_arreg:       .asciiz "Valor de arr_register[RS]: "
str_addr_error: .asciiz "Erro: Endereço inválido!\n"
str_endfinal:    .asciiz "\nEndereco efetivo: "
str_carregado:   .asciiz "\nValor carregado: "
str_invalid_offset:   .asciiz "\noffset invalido: "
str_syscall:        .asciiz "\nsyscall ["
str_invalid_mem:        .asciiz "\nmemoria invalida "
str_param:          .asciiz "] Parâmetro: "
str_newline:        .asciiz "\n"
str_syscall_debug:  .asciiz "SYSCALL: code="
str_invalid_syscall: .asciiz "\nErro: Código inválido: "
str_space:          .asciiz " arg="
arr_register:       .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0, 0, 0
                    .word 0, 0, 0, 0, 0, 0x7FFFEFFC, 0, 0   # arr_register[29] = 0x7FFFEFFC
PC:                 .word 0x00400000                        # registrador PC (program counter)
IR:                 .word 0                                 # registrador IR
RS:                 .word 0
RT:                 .word 0
RD:                 .word 0
# ---------------------------------------- memÃ³ria ----------------------------------------
vet_pilha:          .space 5000                             # vetor de pilha: 0x0x7FFF EFFC
vet_instr:          .space 5000                             # endereco base: 0x0040 0000
vet_data:           .space 5000                             # vetor de dados estaticos: 0x1001 0000
# ------------------------------------- campos instr -------------------------------------
address:            .word 0                                 # campo address              (26 bits)
immediate:          .word 0                                 # campo immediate            (16 bits)
opcode:             .word 0                                 # campo opcode               (6 bits)
shamt:              .word 0                                 # campo shamt (instruÃ§Ãµes R) (5 bits)
funct:              .word 0                                 # campo funct (instruÃ§Ãµes R) (5 bits)
# ---------------------------------------- geral -----------------------------------------
flag_incremento:    .word 0                                 # flag para controlar o incremento em jumps
buffer:             .space 1                                # vamos ler byte-a-byte
f_instr:            .asciiz "instrucoes.bin"	
f_dados:            .asciiz "dados.dat"
str_print1:         .asciiz "\n\ninstrucao buscada (a ser decodificada): "
str_tipor:          .asciiz "\n[tipo R] "
str_tipoi:          .asciiz "\n[tipo I] "
str_tipoj:          .asciiz "\n[tipo J] "
str_opcode:         .asciiz "opcode: "
str_rs:             .asciiz "    rs: "
str_rt:             .asciiz "    rt: "
str_rd:             .asciiz "    rd: "
str_shamt:          .asciiz "    shamt: "
str_funct:          .asciiz "    funct: "
str_imm:            .asciiz "    immediate: "
str_addr:           .asciiz "    address: "
fadd:               .asciiz "\nfazendo a add" 
fcheg:              .asciiz "\nchegou aqui"
str_resultado:      .asciiz "\nresultado: "
str_aux_syscall:    .asciiz "\nresultado da syscall: \n"
# strings dos nomes das instrucoes
str_addu:           .asciiz "\n[addu] "
str_subu:           .asciiz "\n[subu] "
str_addiu:          .asciiz "\n[addiu] "
str_xor:            .asciiz "\n[xor] "
str_lui:            .asciiz "\n[lui] "
str_ori:            .asciiz "\n[ori] "
str_sw:             .asciiz "\n[sw] "
str_lw:             .asciiz "\n[lw] "
str_j:              .asciiz "\n[j] "
str_jr:             .asciiz "\n[jr] "
str_jal:            .asciiz "\n[jal] "
#str_syscall:         .asciiz "\n[syscall] "
str_beq:            .asciiz "\n[beq] " 
str_bne:            .asciiz "\n[bne] "
str_lbu:            .asciiz "\n[lbu] "
str_sb:             .asciiz "\n[sb] "
str_nao_mapeada:    .asciiz "\n[!! instrucao nao mapeada] "
str_jal_debug:      .asciiz "JAL: novo PC = "
str_armazenado: .asciiz " valor armazendado: "


.text
.globl main

_init: 
                    jal main
_finit:
                    move $a0, $v0                           # $a0 = valor de retorno do main
                    li   $v0, 17                            # $v0 = cÃ³digo 17 (exit2)
                    syscall                                 # chamada ao sistema para encerrar o programa

main:
                    jal carregar_instrucoes                 # procedimento que carrega os dados do arquivo.bin no vetor                 
                    jal carregar_dados                      # procedimento que carrega os dados do arquivo.dat no vetor

#                    jal busca_pc                            # procedimento que busca a instruÃ§Ã£o a ser executada
#                    move $s0, $v0                           # move a instruÃ§Ã£o decodificada para $s0

#                    move $a0, $s0                           # move a instruÃ§Ã£o decodificada para $a0 (passando como parametro)
#                    jal decodifica_pc

                    j loop_processador

                    # EXECUTA
                    # executa a instruÃ§Ã£o

                    li $v0, 10                              # $v0 = cÃ³digo de chamada do sistema (exit)
                    syscall                                 # realiza a chamada de sistema com os parametros acima


carregar_instrucoes:
                    addi $sp, $sp, -8                       # aloca espaÃ§o na pilha
                    sw $ra, 4($sp)                          # salva $ra na pilha
                    sw $s0, 0($sp)                          # salva $s0 na pilha

                    li $v0, 13                              # $v0 = cÃ³digo de chamada do sistema (abrir arquivo) 
                    la $a0, f_instr                         # $a0 = endereÃ§o p/ string com o nome do arquivo 
                    li $a1, 0                               # $a1 = flag de abertura de arquivo (modo leitura)
                    syscall                                 # abre o arquivo
#                                                           # descritor do arquivo estÃ¡ em $v0

                    move $t0, $v0                           # $t0 = descritor do arquivo
#                                                           # Ã© uma boa prÃ¡tica nÃ£o manter informaÃ§Ãµes nos registradores $ax e $vx

                    la $t1, vet_instr                       # $t1 = endereÃ§o do vet_instr
                    jal ler_arquivo

                    move $a0, $t0                           # $a0 = descritor do arquivo
                    li $v0, 16                              # $v0 = fechar arquivo
                    syscall                                 # fecha o arquivo

# epÃ­logo (restaurar registradores e destruir stack frame)
                    lw $ra, 4($sp)
                    lw $s0, 0($sp)
                    addi $sp, $sp, 8

                    jr $ra                                  # return address

carregar_dados:
# prÃ³logo (alocar pilha + salvar registradores)
                    addi $sp, $sp, -8
                    sw $ra, 4($sp)
                    sw $s0, 0($sp)

                    li $v0, 13                              # $v0 = cÃ³digo de chamada do sistema (abrir arquivo) 
                    la $a0, f_dados                         # $a0 = endereÃ§o p/ string com o nome do arquivo
                    li $a1, 0                               # $a1 = flag de abertura de arquivo (modo leitura)
                    syscall                                 # abre o arquivo

                    move $t0, $v0                           # $t0 = descritor do arquivo

                    la $t1, vet_data                        # $t1 = endereÃ§o do vet_data
                    jal ler_arquivo                         # leitura do arquivo

                    li $v0, 16                              # $v0 = fechar arquivo
                    move $a0, $t0                           # $a0 = descritor do arquivo
                    syscall                                 # fecha o arquivo

############################################################# epÃ­logo (restaurar registradores e destruir stack frame)
                    lw $ra, 4($sp)
                    lw $s0, 0($sp)
                    addi $sp, $sp, 8

                    jr $ra                                  # return address

ler_arquivo:
                    li $t2, 0                               # $t2 = contador de bytes
ler_loop:
                    li $v0, 14                              # $v0 = ler do arquivo
                    move $a0, $t0                           # $a0 = descritor do arquivo
                    la $a1, buffer                          # $a1 = endereÃ§o do buffer
                    li $a2, 1                               # $a2 = 1
                    syscall                                 # le arquivo

                    beq $v0, $zero, fim_leitura             # se $v0 == 0 -> fim da leitura

                    lb $t3, buffer                          # $t3 = byte lido
                    sb $t3, 0($t1)                          # salva o byte no vetor

                    addi $t1, $t1, 1                        # incrementa endereÃ§o do vetor
                    addi $t2, $t2, 1                        # incrementa o contador

                    j ler_loop                              # continua o loop
fim_leitura:
                    jr $ra                                  # retorna para o $ra

# o professor quer que o programa receba um endereÃ§o "virtual" de memÃ³ria que represente uma
# instruÃ§Ã£o no nosso vetor_instr
# o jeito que eu pensei foi calcular o Ã­ndice do vetor relativo ao endereÃ§o recebido
# a seguinte funÃ§Ã£o recebe um endereÃ§o de PC, subtrai o e.b e retorna o Ã­ndice relativo no array 
endereco_para_offset:                                       #a0 = endereco, #a1 = e. base
                    addi $sp, $sp, -8                       # aloca o espaÃ§o na pilha (para o stack frame)
                    sw $ra, 4($sp)                          # $ra -> salvo na pilha
                    sw $s0, 0($sp)                          # #sp -> salvo na pilha

                    sub $v0, $a0, $a1                       # $v0 = offset (endereÃ§o - base)

                    lw $ra, 4($sp)                          # restaura $ra
                    lw $s0, 0($sp)                          # restaura $s0
                    addi $sp, $sp, 8                        # destroi o stack frame
                    jr $ra                                  # retorna para o $ra

busca_pc:           
                    # ler o endereÃ§o de PC
                    # calcular o indice (offset) com base no pc
                    # ver em vetor_text[indice] qual a instruÃ§Ã£o a ser realizada

                    # Reg       Desc.
                    # $t0       endereÃ§o de pc
                    # $t1       endereÃ§o vetor_inst
                    # $t2       valor PC
                    # $t3       retorno do procedimento endereco_para_offset
                    # $t4       valor guardado na memoria para onde o PC "aponta"

                    addi $sp, $sp, -4                       # "aloca" o espaÃ§o na pilha
                    sw $ra, 0($sp)                          # guarda $ra no srack frame

                    #                                       # fazendo a busca da instruÃ§Ã£o
                    la $t0, PC                              # $t0 = endereÃ§o de PC
                    la $t1, vet_instr                       # $t1 = endereÃ§o base de vetor_instrucoes

                    lw $t2, 0($t0)                          # $t2 = valor de pc (endereÃ§o da prox instruÃ§Ã£o)
                    
                    li $t9, 0x00400000                      # $t9 = e.b segmento de texto
                    move $a0, $t2
                    move $a1, $t9

                    jal endereco_para_offset                # pula para o procedimento endereco_para_offset
                    
                    move $t3, $v0                           # $t3 = retorno do procedimento endereco_para_offset 
#                                                           # equivale ao endereÃ§o na memoria da instruÃ§Ã£o a ser realizada
                  
                    andi $t6, $t3, 0x3                      # verifica se offset é múltiplo de 4
                    bne  $t6, $zero, fim                    # se não for, encerra o programa

                    add $t5, $t1, $t3                       # $t5 = endereço = base + offset
                    lw $t4, 0($t5)                          # $t4 = instrução buscada
                    move $v0, $t4                           # $v0 = retorno do procedimento

                    lw $ra, 0($sp)                          # restaura o $ra
                    addi $sp, $sp, 4                        # "desaloca" espaÃ§o na pilha

                    jr $ra                                  # retorna para $ra

decodifica_pc:
                    # DECODIFICAÃ‡ÃƒO
                    # decodificar os campos da instruÃ§Ã£o lida
                    # guardar na memoria os campos
                    # ver o que representa a instruÃ§Ã£o decodificada
                    addi $sp, $sp, 4
                    sw $ra, 0($sp)

                    move $t0, $a0                            # $t0 = instruÃ§Ã£o buscada
                    
                    srl $t1, $t0, 26                         # $t1 = opcode de $t0
                    la $t2, opcode                           # $t2 = endereço de opcode
                    sw $t1, 0($t2)                           # guarda o opcode na variavel opcode

#                   #                                        # verifica o tipo da instrução
                    beq $t1, $zero, instrucao_R              # instrucao do tipo R
                    li $t3, 2                                # $t3 = 2
                    beq $t1, $t3, instrucao_J                # instrucao do tipo J
                    li $t3, 3                                # $t3 = 3
                    beq $t1, $t3, instrucao_J                # instrucao do tipo J

                    j instrucao_I                            # instrucao do tipo I

instrucao_R:
                    addi $sp, $sp, -4
                    sw $ra, 0($sp)
#                   #                                        # extrai o campo RS
                    srl $t1, $t0, 21                         # 
                    andi $t1, $t1, 0x1F                      #
                    la $t2, RS                               #
                    sw $t1, 0($t2)                           # 
#                   #                                        # extrai o campo RT
                    srl $t1, $t0, 16                         # 
                    andi $t1, $t1, 0x1F                      # 
                    la $t2, RT                               #
                    sw $t1, 0($t2)                           # 
#                   #                                        # extrai o campo RD
                    srl $t1, $t0, 11                         # 
                    andi $t1, $t1, 0x1F                      # 
                    la $t2, RD                               #
                    sw $t1, 0($t2)                           # 
#                   #                                        # extrai o campo shamt
                    srl $t1, $t0, 6                          # 
                    andi $t1, $t1, 0x1F                      # 
                    la $t2, shamt                            #
                    sw $t1, 0($t2)                           # 
#                   #                                        # extrai o campo funct
                    andi $t1, $t0, 0x3F                      # 
                    la $t2, funct                            #
                    sw $t1, 0($t2)                           # 

                    #jal printf_r

                    lw $ra, 0($sp)
                    addi $sp, $sp, 4

                    j fim_decodificacao                      #

instrucao_I:
                    addi $sp, $sp, -4
                    sw $ra, 0($sp)

#                   #                                        # extrai o campo RS
                    srl $t1, $t0, 21                         # 
                    andi $t1, $t1, 0x1F                      #
                    la $t2, RS                               #
                    sw $t1, 0($t2)                           # 
#                   #                                        # extrai o campo RT
                    srl $t1, $t0, 16                         # 
                    andi $t1, $t1, 0x1F                      # 
                    la $t2, RT                               #
                    sw $t1, 0($t2)                           #                
#                   #                                        # extrai o campo immediate
                    andi $t1, $t0, 0xFFFF                    # 
                    la $t2, immediate                        #
                    sw $t1, 0($t2)                           #  

                    la $t3, opcode
                    lw $t4, 0($t3)

                    li   $t5, 0x08                           # addi
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x09                           # addiu
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x23                           # lw
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x2B                           # sw
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x04                           # beq
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x05                           # bne
                    beq  $t4, $t5, extender_immediate
                    li   $t5, 0x0A                           # slti
                    beq  $t4, $t5, extender_immediate
                    j fim_extensao                    

extender_immediate:
                    la $t6, immediate
                    lw $t7, 0($t6)
                    sll $t7, $t7, 16
                    sra $t7, $t7, 16
                    sw $t7, 0($t6)

fim_extensao:
                    #jal printf_i

                    lw $ra, 0($sp)
                    addi $sp, $sp, 4

                    j fim_decodificacao                      # 

instrucao_J:
#                   #                                        # extrai o campo address
                    addi $sp, $sp, -4
                    sw $ra, 0($sp)

                    andi $t1, $t0, 0x03FFFFFF                # 
                    la $t2, address                          #
                    sw $t1, 0($t2)                           #  

                    #jal printf_j

                    lw $ra, 0($sp)
                    addi $sp, $sp, 4

                    j fim_decodificacao                      #

fim_decodificacao:
                    lw $ra, 0($sp)
                    addi $sp, $sp, 4
                    jr $ra

loop_processador:
                    # 1. Verifica se PC atingiu o fim das instruções válidas
                    la $t0, PC
                    lw $t1, 0($t0)          # Carrega PC atual
                    la $t2, vet_instr        # Endereço inicial do código
                    lw $t3, tamanho_codigo  # Tamanho em bytes do código
                    add $t4, $t2, $t3       # Endereço final do código
                    
                    bge $t1, $t4, fim_execucao_sucesso  # Se PC ≥ final do código, termina

                    # 2. Busca segura da instrução
                    jal busca_pc
                    move $s0, $v0           # Guarda instrução

                    # 3. Verifica instrução nula ou inválida
                    beqz $s0, fim_execucao_sucesso  # Se instrução = 0x00000000

                    # 4. Processamento normal
                    move $a0, $s0
                    jal decodifica_pc

                    # Verificação de syscall exit (código 10)
                    la $t0, arr_register
                    lw $t1, 8($t0)          # $v0 (índice 2)
                    li $t2, 10
                    beq $t1, $t2, fim_execucao_sucesso

                    # Controle do PC
                    la $t4, flag_incremento
                    lw $t5, 0($t4)
                    beq $t5, $zero, incrementa_pc
                    li $t5, 0               # Reseta flag
                    sw $t5, 0($t4)
                    j executa_instrucao

incrementa_pc:
                    la $t0, PC
                    lw $t1, 0($t0)
                    addi $t1, $t1, 4       # PC += 4
                    sw $t1, 0($t0)

executa_instrucao:
                    jal verifica_instrucao
                    j loop_processador

fim_execucao_sucesso:
                    # Mensagem de término controlado
                    li $v0, 4
                    la $a0, str_fim_sucesso
                    syscall
                    
                    li $v0, 10              # Exit syscall
                    syscall

printf_r:
# opcode, rs, rt, rd, shamt, funct
                    addi $sp, $sp, -4
                    sw $t0, 0($sp)

                    li $v0, 4                                # print string
                    la $t0, str_tipor
                    move $a0, $t0
                    syscall
                    li $v0, 4                                # print string
                    la $t0, str_opcode
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, opcode
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_rs
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, RS
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_rt
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, RT
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_rd
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, RD
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_shamt
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, shamt
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_funct
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, funct
                    lw $a0, 0($t0)
                    syscall

                    lw $t0, 0($sp)
                    addi $sp, $sp, 4

                    jr $ra

printf_i:
# opcode, rs, rt, rd, shamt, funct
                    addi $sp, $sp, -4
                    sw $t0, 0($sp)

                    li $v0, 4                                # print string
                    la $t0, str_tipoi
                    move $a0, $t0
                    syscall
                    li $v0, 4                                # print string
                    la $t0, str_opcode
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, opcode
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_rs
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, RS
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_rt
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, RT
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_imm
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, immediate
                    lw $a0, 0($t0)
                    syscall

                    jr $ra

printf_j:
# opcode, address
                    addi $sp, $sp, -4
                    sw $t0, 0($sp)

                    li $v0, 4                                # print string
                    la $t0, str_tipoj
                    move $a0, $t0
                    syscall
                    li $v0, 4                                # print string
                    la $t0, str_opcode
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, opcode
                    lw $a0, 0($t0)
                    syscall

                    li $v0, 4                                # print string
                    la $t0, str_addr
                    move $a0, $t0
                    syscall
                    li $v0, 34                               # print hex
                    la $t0, address
                    lw $a0, 0($t0)
                    syscall

                    lw $t0, 0($sp)
                    addi $sp, $sp, 4

                    jr $ra

verifica_instrucao:
                    addi $sp, $sp, -16
                    sw $ra, 0($sp)
                    sw $t0, 4($sp)
                    sw $t1, 8($sp)
                    sw $t2, 12($sp)

                    la $t0, opcode
                    lw $t1, 0($t0)
                    
                    li $t2, 0x00
                    beq $t1, $t2, verifica_funct
                    
                    jal verifica_opI_opJ

                    lw $ra, 0($sp)
                    lw $t0, 4($sp)
                    lw $t1, 8($sp)
                    lw $t2, 12($sp)
                    addi $sp, $sp, 16

                    jr $ra

verifica_funct:  
# INSTRUCOES R: ADD, SUB, AND, OR, SLL, SRL, JR, SYSCALL                                     
# verifica o campo funct para saber qual instrucao executar (apenas tipo R)
                    addi $sp, $sp, -16
                    sw $ra, 0($sp)
                    sw $t0, 4($sp)
                    sw $t1, 8($sp)
                    sw $t2, 12($sp)

                    la $t0, funct 
                    lw $t1, 0($t0)
                    
                    li $t2, 0x20
                    beq $t1, $t2, ADDU
                    li $t2, 0x0C
                    beq $t1, $t2, SYSCALL

                    j fim_verifica_funct
                    
fim_verifica_funct:
                    lw $ra, 0($sp)
                    lw $t0, 4($sp)
                    lw $t1, 8($sp)
                    lw $t2, 12($sp)
                    addi $sp, $sp, 16

                    jr $ra

verifica_opI_opJ:  
# INSTRUCOES I: ADDI, ANDI, ORI, LW, SW, BEQ, BNE
# INSTRUCOES J: J, JAL
# verifica o campo funct para saber qual instrucao executar (apenas tipo R)
                    addi $sp, $sp, -16
                    sw $ra, 0($sp)
                    sw $t0, 4($sp)
                    sw $t1, 8($sp)
                    sw $t2, 12($sp)

                    la $t0, opcode 
                    lw $t1, 0($t0)
                    # I
                    li $t2, 0x08
                    beq $t1, $t2, ADDIU
                    li $t2, 0x09
                    beq $t1, $t2, ADDIU
#                    li $t2, 0x0C
#                    beq $t1, $t2, ANDI
                    li $t2, 0x0f
                    beq $t1, $t2, LUI
                    li $t2, 0x0d
                    beq $t1, $t2, ORI
                    li $t2, 0x23
                    beq $t1, $t2, LW
                    li $t2, 0x2b
                    beq $t1, $t2, SW
#                    li $t2, 0x04
#                    beq $t1, $t2, BEQ
#                    li $t2, 0x05
#                    beq $t1, $t2, BNE
                    # J
                    li $t2, 0x02
                    beq $t1, $t2, J
 #                   li $t2, 0x03
 #                   beq $t1, $t2, JAL
                    j fim_verifica_opI_opJ

fim_verifica_opI_opJ:
                    lw $ra, 0($sp)
                    lw $t0, 4($sp)
                    lw $t1, 8($sp)
                    lw $t2, 12($sp)
                    addi $sp, $sp, 16

                    jr $ra

#########################################################################################
# TIPO R === TIPO R === TIPO R === TIPO R === TIPO R === TIPO R === TIPO R === TIPO R ===
#########################################################################################                
ADDU:               # ADD: ARR_REGISTER[RD] = ARR_REGISTER[RS] + ARR_REGISTER[RT]
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_addu
                    #move $a0, $t0
                    #syscall

                    la $t0, RS                               
                    lw $t1, 0($t0)                           # $t1 = RS
                    la $t0, RT
                    lw $t2, 0($t0)                           # $t2 = RT 
                    la $t0, RD
                    lw $t3, 0($t0)                           # $t3 = RD

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $s1, 4                                # $s1 = 4
################### RS
                    mul $t0, $t1, $s1                        # $t0 = offset RS
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RS
                    lw $t1, 0($t0)                           # $t1 = valor de RS
################### RT
                    mul $t0, $t2, $s1                        # $t0 = offset RT
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RT
                    lw $t2, 0($t0)                           # $t2 = valor de RT

                    addu $s2, $t1, $t2                        # $s2 = resultado
################### RD
                    mul $t0, $t3, $s1                        # $t0 = offset RD
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RD
                    sw $s2, 0($t0)                           # guarda o resultado de RD na memoria

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra
                  
SUBU:               # SUB: ARR_REGISTER[RD] = ARR_REGISTER[RS] - ARR_REGISTER[RT]
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_subu
                    #move $a0, $t0
                    #syscall

                    la $t0, RS                               
                    lw $t1, 0($t0)                           # $t1 = RS
                    la $t0, RT
                    lw $t2, 0($t0)                           # $t2 = RT 
                    la $t0, RD
                    lw $t3, 0($t0)                           # $t3 = RD

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $s1, 4                                # $s1 = 4
################### RS
                    mul $t0, $t1, $s1                        # $t0 = offset RS
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RS
                    lw $t1, 0($t0)                           # $t1 = valor de RS
################### RT
                    mul $t0, $t2, $s1                        # $t0 = offset RT
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RT
                    lw $t2, 0($t0)                           # $t2 = valor de RT

                    subu $s2, $t1, $t2                        # $s2 = resultado
################### RD
                    mul $t0, $t3, $s1                        # $t0 = offset RD
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RD
                    sw $s2, 0($t0)                           # guarda o resultado de RD na memoria

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra
 
XOR:                # XOR: ARR_REGISTER[RD] = ARR_REGISTER[RS] ^ ARR_REGISTER[RT]
                    # addi $rt, $rs, imm
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_xor
                    #move $a0, $t0
                    #syscall

                    la $t0, RS                               
                    lw $t1, 0($t0)                           # $t1 = RS
                    la $t0, RT
                    lw $t2, 0($t0)                           # $t2 = RT 
                    la $t0, RD
                    lw $t3, 0($t0)                           # $t3 = RD

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $s1, 4                                # $s1 = 4
################### RS
                    mul $t0, $t1, $s1                        # $t0 = offset RS
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RS
                    lw $t1, 0($t0)                           # $t1 = valor de RS
################### RT
                    mul $t0, $t2, $s1                        # $t0 = offset RT
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RT
                    lw $t2, 0($t0)                           # $t2 = valor de RT

                    xor $s2, $t1, $t2                        # $s2 = resultado
################### RD
                    mul $t0, $t3, $s1                        # $t0 = offset RD
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RD
                    sw $s2, 0($t0)                           # guarda o resultado de RD na memoria

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra

JR:                 # jr $rs -> JUMP RS 0X0000 0X0000 0X0000 0X001000
                    # pula para o endereco armazendado em RS
                    
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_jr
                    #move $a0, $t0
                    #syscall


                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $s1, 4                                # $s1 = 4
################### RS
                    mul $t0, $t1, $s1                        # $t0 = offset RS
                    add $t0, $s0, $t0                        # $t0 = vet_data + offset RS
                    lw $t1, 0($t0)                           # $t1 = valor de RS

                    la $t0, PC                               # $t0 = endereço de PC
                    sw $t1, 0($t0)                           # guarda o valor de RS (endereço de pulo)em PC

                    la $t4, flag_incremento                  # atualiza a flag de incremento de pc
                    li $t5, 1
                    sw $t5, 0($t4)

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra
                    
#########################################################################################
# TIPO I === TIPO I === TIPO I === TIPO I === TIPO I === TIPO I === TIPO I === TIPO I ===
#########################################################################################
ADDIU:              # ADDIU: ARR_REGISTER[RT] = ARR_REGISTER[RS] + immediate
                    # addi $rt, $rs, imm
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_addiu
                    #move $a0, $t0
                    #syscall

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $t0, 4                                # $t0 = 4

################### RS
                    la $t1, RS                               # $t1 = &RS
                    lw $t2, 0($t1)                           # $t2 =  RS

                    mul $t2, $t2, $t0                        # $t2 = 4 * RS        (offset)
                    add $t2, $s0, $t2                        # $t2 = arr_register + offset
                    lw $s1, 0($t2)                           # $s1 = valor de arr_register[RS]                    

################### RT
                    la $t1, RT                               # $t1 = &RT
                    lw $t2, 0($t1)                           # $t2 =  RT 

                    mul $t2, $t2, $t0                        # $t2 = 4 * RT        (offset)
                    add $t2, $s0, $t2                        # $t2 = arr_register + offset
                    move $s2, $t2                            # $s2 = arr_register + offset

################### immediate
                    la $t1, immediate
                    lw $s3, 0($t1)                           # $s3 = immediate

                    # aqui temos os valores necessarios em:
                    # $s0 = endereço base arr_register 
                    # $s1 = valor    arr_register[RS]
                    # $s2 = endereço arr_register[RT]
                    # $s3 = immediate

                    addu $t9, $s1, $s3                       # $t9 = array[RS] + immediate
                    sw $t9, 0($s2)                           # guarda no vetor o resultado
                    # "PRINTFS"
                    #li $v0, 4
                    #la $a0, str_resultado
                    #syscall
                    #li $v0, 34
                    #move $a0, $t9
                    #syscall

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra

LUI:                # LUI $rt, immediate -> $rt = immediate << 16
                    # addi $rt, $rs, imm
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_lui
                    #move $a0, $t0
                    #syscall

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $t0, 4                                # $t0 = 4

################### RT
                    la $t1, RT                               # $t1 = &RT
                    lw $t2, 0($t1)                           # $t2 =  RT 

                    mul $t2, $t2, $t0                        # $t2 = 4 * RT        (offset)
                    add $t2, $s0, $t2                        # $t2 = arr_register + offset end. rt vetor
                    
# immediate
                    la $t1, immediate
                    lw $t5, 0($t1)                           # $t5 = valor de immediate

                    sll $t3, $t5, 16                         # $t3 = immediate << 16 

                    sw $t3, 0($t2)                           # guardar em vetor[rt]


                    #li $v0, 4                                # print string
                    #la $t0, str_resultado
                    #move $a0, $t0
                    #syscall
                    #li $v0, 34                                # print string
                   # move $a0, $t3
                    #syscall

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra

ORI:                # ORI $rt, $rs, immediate -> $rt = $rs | (zero_extended(immediate))
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4                                # print string
                    #la $t0, str_ori
                    #move $a0, $t0
                    #syscall

                    la $s0, arr_register                     # $s0 = endereço base arr_register
                    li $t0, 4                                # $t0 = 4

################### RS
                    la $t1, RS                               # $t1 = &RS
                    lw $t2, 0($t1)                           # $t2 =  RS

                    mul $t2, $t2, $t0                        # $t2 = 4 * RS        (offset)
                    add $t2, $s0, $t2                        # $t2 = arr_register + offset
                    lw $s1, 0($t2)                           # $s1 = valor de arr_register[RS]                    

################### RT
                    la $t1, RT                               # $t1 = &RT
                    lw $t2, 0($t1)                           # $t2 =  RT 

                    mul $t2, $t2, $t0                        # $t2 = 4 * RT        (offset)
                    add $t2, $s0, $t2                        # $t2 = arr_register + offset

                    # immediate
                    la $t1, immediate
                    lw $t3, 0($t1)                           # $t3 = valor de immediate

                    or $t4, $s1, $t3                         # $t4 = arr_register[rs] or immediate

                    sw $t4, 0($t2)                            # guarda o valor no vetor[rt]

                    #li $v0, 4                                # print string
                    #la $t0, str_resultado
                    #move $a0, $t0
                    #syscall
                    #li $v0, 34                                # print string
                    #move $a0, $t4
                    #syscall

                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8

                    jr $ra

LW:                 # LW: arr_register[RT] = MEM[arr_register[RS] + imm]
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                    #li $v0, 4
                    #la $t0, str_lw
                    #move $a0, $t0
                    #syscall

                    la $s0, arr_register
                    li $t0, 4

################### RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)                            # $s1 = arr_register[RS]

################### RT
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    move $t3, $t2                             # salvar endereço de RT

################### immediate
                    la $t1, immediate
                    lw $s2, 0($t1)

                    add $s3, $s1, $s2                         # $s3 = endereço efetivo

################### PRINTS
                    #li $v0, 4
                    #la $a0, str_arreg
                    #syscall  
                    #li $v0, 34
                    #move $a0, $s1
                    #syscall                                  # imprime arr_register[RS]

#                    li $v0, 4
#                    la $a0, str_imm
#                    syscall                                  
#                    li $v0, 34
#                    move $a0, $s2
#                    syscall                                  # imprime immediate

#                    li $v0, 4
#                    la $a0, str_endfinal
#                    syscall  
#                    li $v0, 34
#                    move $a0, $s3
#                    syscall                                  # imprime endereço final

################### Verificação de memória
                    li $t4, 0x10010000
                    li $t6, 5000
                    subu $t7, $s3, $t4
                    blt $t7, $t6, LW_DATA

                    li $t4, 0x7FFFEFFC
                    subu $t7, $t4, $s3
                    blt $t7, $t6, LW_STACK

                    li $v0, 4
                    la $a0, str_invalid_mem
                    syscall
                    j FIM_LW

LW_DATA:
                    la $t8, vet_data
                    addu $t8, $t8, $t7
                    lw $t9, 0($t8)
                    j ARMAZENA

LW_STACK:
                    la $t8, vet_pilha
                    addu $t8, $t8, $t7
                    lw $t9, 0($t8)
                    j ARMAZENA

ARMAZENA:
                    sw $t9, 0($t3)                             # arr_register[RT] = valor carregado

                    #li $v0, 4
                    #la $a0, str_carregado
                   # syscall  
                    #li $v0, 34
                 #   move $a0, $t9
                #    syscall                                  # imprime valor carregado

FIM_LW:
                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8
                    jr $ra

SW:                 # SW: MEM[arr_register[RS] + imm] = arr_register[RT]
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                #    li $v0, 4
               #     la $t0, str_sw
              #      move $a0, $t0
             #       syscall

                    la $s0, arr_register
                    li $t0, 4

################### RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)                            # $s1 = arr_register[RS]

################### RT
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s2, 0($t2)                            # $s2 = arr_register[RT]

################### immediate
                    la $t1, immediate
                    lw $s3, 0($t1)

                    add $s4, $s1, $s3                         # endereço efetivo

################### PRINTS
                    
                  #  li $v0, 4
                 #   la $a0, str_arreg
                 #   syscall  
                 #   li $v0, 34
                #    move $a0, $s1
               #     syscall                                  # imprime arr_register[RS]

                 #   li $v0, 4
                 #   la $a0, str_imm
                #    syscall                                  # imprime immediate
               #     li $v0, 34
               #     move $a0, $s3
               #     syscall                                  # imprime immediate

                  #  li $v0, 4
                 #   la $a0, str_endfinal
                #    syscall  
                #    li $v0, 34
                #    move $a0, $s4
                #    syscall                                  # imprime endereço final

                    li $t4, 0x10010000
                    li $t6, 5000
                    subu $t7, $s4, $t4
                    blt $t7, $t6, SW_DATA

                    li $t4, 0x7FFFEFFC
                    subu $t7, $t4, $s4
                    blt $t7, $t6, SW_STACK

                    li $v0, 4
                    la $a0, str_invalid_mem
                    syscall
                    j FIM_SW
SW_DATA:
                    la $t8, vet_data
                    addu $t8, $t8, $t7
                    sw $s2, 0($t8)
                    j FIM_SW
SW_STACK:
                    la $t8, vet_pilha
                    addu $t8, $t8, $t7
                    sw $s2, 0($t8)
                    j FIM_SW
FIM_SW:
                   # li $v0, 4
                  #  la $a0, str_armazenado
                 #   syscall  
                  #  li $v0, 34
                  #  move $a0, $s2
                 #   syscall                                  # imprime valor armazenado
                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8
                    jr $ra

LBU:                # LBU: arr_register[RT] = zero_extend(MEM[arr_register[RS] + imm])
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                   # li $v0, 4
                 #   la $t0, str_lbu
                #    move $a0, $t0
             #       syscall

                    la $s0, arr_register
                    li $t0, 4

                    # Carrega RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)         # $s1 = arr_register[RS]

                    # Carrega RT (apenas para endereço de destino)
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t3, $s0, $t2      # $t3 = endereço de RT no arr_register

                    # Carrega immediate
                    la $t1, immediate
                    lw $s2, 0($t1)

                    # Calcula endereço efetivo
                    add $s3, $s1, $s2      # $s3 = endereço efetivo

                    # Debug prints
                 #   li $v0, 4
               #     la $a0, str_arreg
               #     syscall  
              #      li $v0, 34
                #    move $a0, $s1
                #    syscall

                 #   li $v0, 4
                  #  la $a0, str_imm
                  #  syscall  
                  #  li $v0, 34
                  #  move $a0, $s2
                  #  syscall

                   # li $v0, 4
                   # la $a0, str_endfinal
                   # syscall  
                   # li $v0, 34
                   # move $a0, $s3
                   # syscall

                    # Verificação de memória
                    li $t4, 0x10010000     # Base da memória de dados
                    li $t6, 5000           # Tamanho máximo
                    subu $t7, $s3, $t4     # Offset
                    blt $t7, $t6, LBU_DATA

                    li $t4, 0x7FFFEFFC     # Base da pilha
                    subu $t7, $t4, $s3
                    blt $t7, $t6, LBU_STACK

                    li $v0, 4
                    la $a0, str_invalid_mem
                    syscall
                    j FIM_LBU

LBU_DATA:
                    la $t8, vet_data
                    addu $t8, $t8, $t7
                    lbu $t9, 0($t8)        # Carrega byte com zero-extend
                    j ARMAZENA_LBU

LBU_STACK:
                    la $t8, vet_pilha
                    addu $t8, $t8, $t7
                    lbu $t9, 0($t8)        # Carrega byte com zero-extend

ARMAZENA_LBU:
                    sw $t9, 0($t3)         # Armazena no registrador RT

                   # li $v0, 4
                   # la $a0, str_carregado
                   # syscall  
                    #li $v0, 36             # Print unsigned integer
                   # move $a0, $t9
                   # syscall

FIM_LBU:
                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8
                    jr $ra

SB:                 # SB: MEM[arr_register[RS] + imm] = byte_menos_significativo(arr_register[RT])
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)

                  #  li $v0, 4
                  #  la $t0, str_sb
                  #  move $a0, $t0
                  #  syscall

                    la $s0, arr_register
                    li $t0, 4

                    # Carrega RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)         # $s1 = arr_register[RS]

                    # Carrega RT
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s2, 0($t2)         # $s2 = arr_register[RT]
                    andi $s2, $s2, 0xFF    # Pega apenas o byte menos significativo

                    # Carrega immediate
                    la $t1, immediate
                    lw $s3, 0($t1)

                    # Calcula endereço efetivo
                    add $s4, $s1, $s3      # $s4 = endereço efetivo

                    # Debug prints
                   # li $v0, 4
                   # la $a0, str_arreg
                   # syscall  
                   # li $v0, 34
                   # move $a0, $s1
                   # syscall

                   # li $v0, 4
                   # la $a0, str_imm
                   # syscall  
                   # li $v0, 34
                   # move $a0, $s3
                   # syscall

                   # li $v0, 4
                   # la $a0, str_endfinal
                    #syscall  
                   # li $v0, 34
                   # move $a0, $s4
                   # syscall

                    # Verificação de memória
                    li $t4, 0x10010000     # Base da memória de dados
                    li $t6, 5000           # Tamanho máximo
                    subu $t7, $s4, $t4     # Offset
                    blt $t7, $t6, SB_DATA

                    li $t4, 0x7FFFEFFC     # Base da pilha
                    subu $t7, $t4, $s4
                    blt $t7, $t6, SB_STACK

                    li $v0, 4
                    la $a0, str_invalid_mem
                    syscall
                    j FIM_SB

SB_DATA:
                    la $t8, vet_data
                    addu $t8, $t8, $t7
                    sb $s2, 0($t8)         # Armazena apenas 1 byte
                    j FIM_SB

SB_STACK:
                    la $t8, vet_pilha
                    addu $t8, $t8, $t7
                    sb $s2, 0($t8)         # Armazena apenas 1 byte

FIM_SB:
                   # li $v0, 4
                  #  la $a0, str_armazenado
                  #  syscall  
                  #  li $v0, 34
                 #   move $a0, $s2
                 #   syscall
                    lw $ra, 0($sp)
                    lw $s0, 4($sp)
                    addi $sp, $sp, 8
                    jr $ra

BEQ:                # BEQ: if (RS == RT) PC += imm << 2
                    addi $sp, $sp, -12
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)
                    sw $s1, 8($sp)

                    #li $v0, 4
                    #la $a0, str_beq
                    #syscall

                    la $s0, arr_register
                    li $t0, 4

                    # Carrega RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)         # $s1 = arr_register[RS]

                    # Carrega RT
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s2, 0($t2)         # $s2 = arr_register[RT]

                    # Carrega immediate
                    la $t1, immediate
                    lw $s3, 0($t1)         # $s3 = immediate

                    # Debug prints
                    #li $v0, 4
                    #la $a0, str_rs
                   # syscall
                    #li $v0, 34
                   # move $a0, $s1
                   # syscall

                 #   li $v0, 4
                  #  la $a0, str_rt
                  #  syscall
                   # li $v0, 34
                   # move $a0, $s2
                  #  syscall

                   # li $v0, 4
                   # la $a0, str_imm
                    #syscall
                 #   li $v0, 1
                #    move $a0, $s3
               #     syscall

                    # Comparação
                    bne $s1, $s2, beq_nao_tomar

                    # Calcula novo PC
                    lw $t0, PC
                    sll $t1, $s3, 2        # immediate << 2
                    addu $t0, $t0, $t1     # PC + (imm << 2)

                    # Atualiza PC
                    sw $t0, PC

                    # Desativa incremento automático
                    li $t1, 1
                    sw $t1, flag_incremento

                    li $v0, 4
                    la $a0, str_branch_taken
                    syscall
                    j beq_fim

beq_nao_tomar:
                    li $v0, 4
                    la $a0, str_branch_not_taken
                    syscall

beq_fim:
                    lw $s1, 8($sp)
                    lw $s0, 4($sp)
                    lw $ra, 0($sp)
                    addi $sp, $sp, 12
                    jr $ra

BNE:                # BNE: if (RS != RT) PC += imm << 2
                    addi $sp, $sp, -12
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)
                    sw $s1, 8($sp)

                   # li $v0, 4
                    #la $a0, str_bne
                   # syscall

                    la $s0, arr_register
                    li $t0, 4

                    # Carrega RS
                    la $t1, RS
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s1, 0($t2)         # $s1 = arr_register[RS]

                    # Carrega RT
                    la $t1, RT
                    lw $t2, 0($t1)
                    mul $t2, $t2, $t0
                    add $t2, $s0, $t2
                    lw $s2, 0($t2)         # $s2 = arr_register[RT]

                    # Carrega immediate
                    la $t1, immediate
                    lw $s3, 0($t1)         # $s3 = immediate

                    # Debug prints
                   # li $v0, 4
                   # la $a0, str_rs
                   # syscall
                   # li $v0, 34
                  #  move $a0, $s1
                  #  syscall

                  #  li $v0, 4
                  #  la $a0, str_rt
                 #   syscall
                    #li $v0, 34
                   # move $a0, $s2
                   # syscall

                  #  li $v0, 4
                #    la $a0, str_imm
                #    syscall
                #    li $v0, 1
               #     move $a0, $s3
                #    syscall

                    # Comparação
                    beq $s1, $s2, bne_nao_tomar

                    # Calcula novo PC
                    lw $t0, PC
                    sll $t1, $s3, 2        # immediate << 2
                    addu $t0, $t0, $t1     # PC + (imm << 2)

                    # Atualiza PC
                    sw $t0, PC

                    # Desativa incremento automático
                    li $t1, 1
                    sw $t1, flag_incremento

                    li $v0, 4
                    la $a0, str_branch_taken
                    syscall
                    j bne_fim

bne_nao_tomar:
                    li $v0, 4
                    la $a0, str_branch_not_taken
                    syscall

bne_fim:
                    lw $s1, 8($sp)
                    lw $s0, 4($sp)
                    lw $ra, 0($sp)
                    addi $sp, $sp, 12
                    jr $ra

#########################################################################################
# TIPO J === TIPO J === TIPO J === TIPO J === TIPO J === TIPO J === TIPO J === TIPO J ===
#########################################################################################
J:                  # J: JUMP -> ADDRESS (28 BITS)
# e. base 0x00400000
#a0 = endereco, #a1 = e. base, v0 = resposta (index)
                    addi $sp, $sp, -4
                    sw $ra, 0($sp)

                   # li $v0, 4                                # print string
                   # la $a0, str_j
                   # syscall

                    li $t9, 0x00400000                        # endereço base vet_text
                    la $t0, address                           # $t0 = variavel address       
                    lw $t1, 0($t0)                            # $t1 = valor de address (end. para pular)
                    
                    sll $t1, $t1, 2                           # $t1 = address << 2
                    li $t2, 0xF0000000                        # mascara
                    not $t2, $t2                              # $t2 = 0x0FFFFFFF
                    and $t1, $t1, $t2                         # zera os 4 bits mais altos

                    la $t3, PC
                    lw $t4, 0($t3)
                    srl $t5, $t4, 28
                    sll $t5, $t5, 28
                    or $t1, $t1, $t5

                    sw $t1, 0($t3)

                    la $t4, flag_incremento
                    li $t5, 1
                    sw $t5, 0($t4)

                    lw $ra, 0($sp)
                    addi $sp, $sp, 4
                    jr $ra

#########################################################################################
# SYSCALL === SYSCALL === SYSCALL === SYSCALL === SYSCALL === SYSCALL === SYSCALL === 
#########################################################################################
SYSCALL:
                    addi $sp, $sp, -16
                    sw $ra, 0($sp)
                    sw $s0, 4($sp)
                    sw $s1, 8($sp)
                    sw $s2, 12($sp)

                    # Carrega código da syscall (arr_register[2])
                    la $s0, arr_register
                    li $t0, 2
                    sll $t1, $t0, 2
                    add $t1, $s0, $t1
                    lw $s1, 0($t1)         # $s1 = código syscall

                    # Carrega parâmetro (arr_register[4])
                    li $t0, 4
                    sll $t1, $t0, 2
                    add $t1, $s0, $t1
                    lw $s2, 0($t1)         # $s2 = parâmetro

                    # Debug: mostra syscall e parâmetro
                    #li $v0, 4
                   # la $a0, str_syscall
                 #   syscall
                #    li $v0, 1
               #     move $a0, $s1
              #      syscall
              #      li $v0, 4
             #       la $a0, str_param
            #        syscall
            #        li $v0, 34
            #        move $a0, $s2
            #        syscall
             #       li $v0, 4
             #       la $a0, str_newline
             #       syscall

                    # Prepara para syscall real
                    move $v0, $s1         # Código da syscall

                    # Verifica tipo de parâmetro
                    li $t0, 4              # print_string
                    beq $s1, $t0, syscall_string
                    li $t0, 8              # read_string
                    beq $s1, $t0, syscall_string
                    li $t0, 9              # sbrk
                    beq $s1, $t0, syscall_string

                    # Outras syscalls (usa valor direto)
                    move $a0, $s2
                    j exec_syscall

syscall_string:
                    # Verifica se endereço está no segmento de dados
                    li $t0, 0x10010000     # Início da memória estática
                    li $t1, 0x10020000     # Fim da memória estática
                    blt $s2, $t0, addr_error
                    bge $s2, $t1, addr_error

                    # Converte para offset no vet_data
                    sub $t2, $s2, $t0      # Calcula offset
                    la $a0, vet_data
                    add $a0, $a0, $t2      # Endereço real no simulador

exec_syscall:
                    syscall
                    j syscall_end

addr_error:
                    #li $v0, 4
                    #la $a0, str_addr_error
                    #syscall

syscall_end:
                    lw $s2, 12($sp)
                    lw $s1, 8($sp)
                    lw $s0, 4($sp)
                    lw $ra, 0($sp)
                    addi $sp, $sp, 16
                    jr $ra

JAL:                
                    addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $t0, 4($sp)          # Preserva $t0
                    
                    la $t0, vet_data        # e. base vetor_data
                    
                    # guarda PC+4 em $ra reg[31]
                    lw $t1, PC             # carrega PC atual
                    addi $t1, $t1, 4       # PC + 4 (endereço de retorno)
                    
                    li $t2, 31             # indice do registrador $ra
                    mul $t3, $t2, 4        # offset
                    addu $t3, $t0, $t3     # end. base + offset
                    sw $t1, 0($t3)         # Armazena PC+4 em $ra
                    
 
                    # calcula novo endereço de jump
                    lw $t1, address        # Carrega address (26 bits)
                    sll $t1, $t1, 2        # address << 2 (28 bits)
                    
                    # upper 4 bits do PC atual
                    lw $t2, PC
                    srl $t2, $t2, 28       # isola bits 31-28
                    sll $t2, $t2, 28       # posiciona nos bits altos
                    
                    or $t1, $t1, $t2       # Novo PC = [31:28]PC | (address << 2)

                    # atualiza PC e flag
                    sw $t1, PC             # Atualiza PC
                    
                    li $t2, 1
                    sw $t2, flag_incremento # desativa incremento automático
                    
                    li $v0, 4
                    la $a0, str_jal_debug
                    syscall
                    li $v0, 34
                    lw $a0, PC
                    syscall
                    
                    lw $t0, 4($sp)
                    lw $ra, 0($sp)
                    addi $sp, $sp, 8
                    jr $ra

fim:
                    li $a0, 10
                    syscall
