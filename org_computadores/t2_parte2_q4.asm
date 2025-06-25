.data
        result_fat:      .asciiz "o fatorial é: "           # string resultado do fatorial
        result_pow:      .asciiz "a exponenciação é: "      # string resultado da exponenciação
        result_cos:      .asciiz "o cosseno é: "            # string resultado do cosseno
        one_double:      .double 1.0                        # constante 1.0
        entrada:         .double 0.21                       # entrada: base 4.0
        two_double:      .double 2.0

.text
        .globl main

.macro print_str (%str)
        li $v0, 4                                          # código para imprimir string
        la $a0, %str                                       # carrega endereço da string
        syscall                                            # chamada do sistema
.end_macro

.macro print_int (%reg)
        li $v0, 1                                          # código para imprimir inteiro
        move $a0, %reg                                     # move valor para $a0
        syscall                                            # chamada do sistema
.end_macro

.macro print_double (%reg)
        li $v0, 3                                          # código para imprimir double
        mov.d $f12, %reg                                   # move double para $f12
        syscall                                            # chamada do sistema
.end_macro

main:
        # Garante alinhamento de 8 bytes
        addiu $sp, $sp, -24                                # aloca 24 bytes (múltiplo de 8)
        andi $sp, $sp, -8                                  # força alinhamento de 8 bytes
        sw $ra, 0($sp)                                     # salva endereço de retorno
        s.d $f20, 8($sp)                                   # salva $f20 (alinhado em 8)

        la $t0, entrada
        l.d $f12, 0($t0)
        jal cos_d
        mov.d $f20, $f0                                    # usa $f20 para preservar o valor
        print_str(result_cos)
        print_double($f20)

        l.d $f20, 8($sp)                                   # restaura $f20
        lw $ra, 0($sp)                                     # restaura endereço de retorno
        addiu $sp, $sp, 24                                 # desaloca espaço da pilha
        li $v0, 10                                         # código para encerrar programa
        syscall                                            # chamada do sistema

# ----------------------------
# fatorial iterativo
# Entrada: $a0 = n, Saída: $v0 = n!
factorial:
        addiu $sp, $sp, -16                               # aloca espaço na pilha (múltiplo de 8)
        sw $ra, 0($sp)                                    # salva endereço de retorno
        sw $s0, 4($sp)                                    # salva $s0
        sw $s1, 8($sp)                                    # salva $s1

        li $v0, 1                                         # inicializa resultado com 1
        beq $a0, $zero, end_factorial                     # se n == 0, vai para fim
        li $s0, 1                                         # carrega 1 em $s0 (registro salvo)
        beq $a0, $s0, end_factorial                       # se n == 1, vai para fim

        move $s0, $a0                                     # $s0 = n (usa registro salvo)

factorial_loop:
        mul $v0, $v0, $s0                                 # $v0 *= $s0
        subi $s0, $s0, 1                                  # $s0--
        bgt $s0, 1, factorial_loop                        # continua se $s0 > 1

end_factorial:
        lw $s1, 8($sp)                                    # restaura $s1
        lw $s0, 4($sp)                                    # restaura $s0
        lw $ra, 0($sp)                                    # restaura endereço de retorno
        addiu $sp, $sp, 16                                # desaloca espaço da pilha
        jr $ra                                            # retorna

# ----------------------------
# pow: calcula $f12 ^ $a0 -> $f0 (double)
pow:
        addiu $sp, $sp, -32                               # aloca espaço na pilha (múltiplo de 8)
        sw $ra, 0($sp)                                    # salva endereço de retorno
        sw $s0, 4($sp)                                    # salva $s0
        s.d $f20, 8($sp)                                  # salva $f20 (alinhado em 8)
        s.d $f22, 16($sp)                                 # salva $f22

        l.d $f20, one_double                              # $f20 = 1.0
        beq $a0, $zero, pow_end                           # se expoente = 0, retorna 1.0

        bgt $a0, $zero, pow_positive                      # se expoente > 0, vai para positivo
        sub $a0, $zero, $a0                              # expoente = -expoente
        jal pow_positive                                  # calcula pow(base, -exp)
        l.d $f22, one_double                             # $f22 = 1.0
        div.d $f0, $f22, $f0                              # $f0 = 1 / $f0
        j pow_end                                         # fim

pow_positive:
        mov.d $f20, $f12                                  # inicia $f20 com base
        li $s0, 1                                         # $s0 = 1
        beq $a0, $s0, pow_positive_end                    # se exp == 1, fim
        sub $a0, $a0, 1                                   # exp--

pow_loop:
        beq $a0, $zero, pow_positive_end                  # fim se exp == 0
        mul.d $f20, $f20, $f12                            # $f20 *= base
        sub $a0, $a0, 1                                   # exp--
        j pow_loop                                        # repete

pow_positive_end:
        mov.d $f0, $f20                                   # move resultado para $f0

pow_end:
        l.d $f22, 16($sp)                                 # restaura $f22
        l.d $f20, 8($sp)                                  # restaura $f20
        lw $s0, 4($sp)                                    # restaura $s0
        lw $ra, 0($sp)                                    # restaura endereço de retorno
        addiu $sp, $sp, 32                                # desaloca espaço da pilha
        jr $ra                                            # retorna

# entrada: $f12 -> valor a calcular o cosseno
# saida  : $f0  -> cosseno
cos_d:
        addiu $sp, $sp, -64                               # aloca espaço na pilha (múltiplo de 8)
        sw $ra, 0($sp)                                    # salva $ra
        sw $s0, 4($sp)                                    # salva $s0
        sw $s1, 8($sp)                                    # salva $s1
        sw $s2, 12($sp)                                   # salva $s2
        s.d $f20, 16($sp)                                 # salva $f20 (alinhado em 8)
        s.d $f22, 24($sp)                                 # salva $f22
        s.d $f24, 32($sp)                                 # salva $f24
        s.d $f26, 40($sp)                                 # salva $f26
        s.d $f28, 48($sp)                                 # salva $f28

        li $s0, 1                                         # Inicia contador em 1 (i=1 to 7)
        li $s1, 7                                         # Número máximo de iterações
        
        l.d $f20, one_double                              # Acumulador inicia em 1.0 (termo 0)
        
        # Calcula x² uma vez para otimização
        mul.d $f22, $f12, $f12                           # $f22 = x²
    
cos_loop:
        bgt $s0, $s1, cos_end
        
        sll $s2, $s0, 1                                  # $s2 = (2*i)
        
        # Calcular a potência x^(2i)
        mov.d $f12, $f22                                 # Carrega x²
        move $a0, $s0                                    # Expoente i (pois já temos x²)
        jal pow
        mov.d $f24, $f0                                  # $f24 = x^(2i)
        
        # Calcular o fatorial (2i)!
        move $a0, $s2
        jal factorial
        mtc1 $v0, $f26
        cvt.d.w $f26, $f26                               # Converte para double
        
        div.d $f28, $f24, $f26                           # $f28 = termo atual (x^(2i))/(2i)!
        
        # Verifica se i é ímpar para subtrair
        andi $t0, $s0, 1                                # Verifica o bit menos significativo
        beqz $t0, cos_par                               # Se par, adiciona
        
cos_impar:
        sub.d $f20, $f20, $f28                          # Subtrai termo quando i é ímpar
        j cos_increment
        
cos_par:
        add.d $f20, $f20, $f28                          # Adiciona termo quando i é par
        
cos_increment:
        addiu $s0, $s0, 1                               # Incrementa contador (i++)
        j cos_loop
        
cos_end:
        mov.d $f0, $f20
        l.d $f28, 48($sp)                               # restaura $f28
        l.d $f26, 40($sp)                               # restaura $f26
        l.d $f24, 32($sp)                               # restaura $f24
        l.d $f22, 24($sp)                               # restaura $f22
        l.d $f20, 16($sp)                               # restaura $f20
        lw $s2, 12($sp)                                 # restaura $s2
        lw $s1, 8($sp)                                  # restaura $s1
        lw $s0, 4($sp)                                  # restaura $s0
        lw $ra, 0($sp)                                  # restaura $ra
        addiu $sp, $sp, 64                              # desaloca espaço da pilha
        jr $ra
