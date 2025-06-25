.data
resultado_fatorial:     .asciiz "o fatorial é: "           
resultado_potenciacao:  .asciiz "a potenciacao é: "
resultado_cosseno:      .asciiz "o cosseno é: "
entrada_utilizada:      .asciiz "entrada = "
newline:                .asciiz "\n"
um_double:              .double 1.0
dois_double:            .double 2.0
entrada:                .double 0.21

.text
.globl main

.macro print_str (%str)
        li $v0, 4
        la $a0, %str
        syscall
.end_macro

.macro print_int (%reg)
        li $v0, 1
        move $a0, %reg
        syscall
.end_macro

.macro print_double (%reg)
        li $v0, 3
        mov.d $f12, %reg
        syscall
.end_macro

main:
        addiu $sp, $sp, -24
        andi $sp, $sp, -8
        sw $ra, 0($sp)
        s.d $f20, 8($sp)

        la $t0, entrada
        l.d $f12, 0($t0)
        print_str(entrada_utilizada)
        print_double($f12)

        jal cos_d
        mov.d $f20, $f0

        print_str(newline)
        print_str(resultado_cosseno)
        print_double($f20)

        l.d $f20, 8($sp)
        lw $ra, 0($sp)
        addiu $sp, $sp, 24
        li $v0, 10
        syscall

# entrada: $a0 = x, 
# saÃ­da:   $v0 = x!
fatorial:
        addiu $sp, $sp, -16
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        sw $s1, 8($sp)

        li $v0, 1
        beq $a0, $zero, fim_fatorial
        li $s0, 1
        beq $a0, $s0, fim_fatorial

        move $s0, $a0

loop_fatorial:
        mul $v0, $v0, $s0                                       # $v0 *= $s0
        subi $s0, $s0, 1                                        # $s0--
        bgt $s0, 1, loop_fatorial

fim_fatorial:
        lw $s1, 8($sp)
        lw $s0, 4($sp)
        lw $ra, 0($sp)
        addiu $sp, $sp, 16
        jr $ra

# entrada_1: base      $f12 (numero em ponto flutuante precisao dupla)
# entrada_2: expoente  $a0  (numero ponto fixo)
# saÃ­da    : resultado $f0 = $f12 ^ $a0 
exponenciacao:
        addiu $sp, $sp, -32
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        s.d $f20, 8($sp)
        s.d $f22, 16($sp)

        l.d $f20, um_double
        beq $a0, $zero, fim_exponenciacao

        bgt $a0, $zero, exponenciacao_positiva                  
        sub $a0, $zero, $a0                                     # expoente = -expoente
        jal exponenciacao_positiva                              # calcula exponenciacao (base, -exp)
        l.d $f22, um_double                                     # $f22 = 1.0
        div.d $f0, $f22, $f0                                    # $f0 = 1 / $f0
        j fim_exponenciacao                                     # fim

exponenciacao_positiva:
        mov.d $f20, $f12                                        # inicia $f20 com base
        li $s0, 1                                               # $s0 = 1
        beq $a0, $s0, fim_exponenciacao_positiva                # encerra se exp == 1
        sub $a0, $a0, 1                                         # exp--

loop_exponenciacao:
        beq $a0, $zero, fim_exponenciacao_positiva              # encerra se exp == 0
        mul.d $f20, $f20, $f12                                  # $f20 *= base
        sub $a0, $a0, 1                                         # exp--
        j loop_exponenciacao

fim_exponenciacao_positiva:
        mov.d $f0, $f20

fim_exponenciacao:
        l.d $f22, 16($sp)
        l.d $f20, 8($sp)
        lw $s0, 4($sp)
        lw $ra, 0($sp)
        addiu $sp, $sp, 32
        jr $ra

# entrada: $f12 -> x
# saÃ­da  : $f0  -> cosseno(x)
cos_d:
        addiu $sp, $sp, -64
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        sw $s1, 8($sp)
        sw $s2, 12($sp)
        s.d $f20, 16($sp)
        s.d $f22, 24($sp)
        s.d $f24, 32($sp)
        s.d $f26, 40($sp)
        s.d $f28, 48($sp)

        li $s0, 1                                         # i = 1
        li $s1, 7                                         # max_iteraÃ§Ãµes = 7
        
        l.d $f20, um_double                               # acumulador = 1.0 (precisao dupla)
        
        mul.d $f22, $f12, $f12                            # $f22 = x^2
    
cos_loop:
        bgt $s0, $s1, cos_end
        
        sll $s2, $s0, 1                                   # $s2 = (2*i)
        
        # calcular a potÃªncia x^(2i)
        mov.d $f12, $f22                                 
        move $a0, $s0                                    
        jal exponenciacao
        mov.d $f24, $f0                                   # $f24 = x^(2i)
        
        # calcular o fatorial (2i)!
        move $a0, $s2
        jal fatorial
        mtc1 $v0, $f26
        cvt.d.w $f26, $f26                               # converte para precisÃ£o dupla
        
        div.d $f28, $f24, $f26                           # $f28 = (x^(2i))/(2i)!
        
        andi $t0, $s0, 1                                 # verifica paridade do contador (i)
        beqz $t0, cos_par                               
        
cos_impar:
        sub.d $f20, $f20, $f28                           # i impar == subtraÃ§Ã£o
        j cos_increment
        
cos_par:
        add.d $f20, $f20, $f28                           # i par == adiÃ§Ã£o
        
cos_increment:
        addiu $s0, $s0, 1                                # incrementa contador (i++)
        j cos_loop
        
cos_end:
        mov.d $f0, $f20
        l.d $f28, 48($sp)
        l.d $f26, 40($sp)
        l.d $f24, 32($sp)
        l.d $f22, 24($sp)
        l.d $f20, 16($sp)
        lw $s2, 12($sp)
        lw $s1, 8($sp)
        lw $s0, 4($sp)
        lw $ra, 0($sp)
        addiu $sp, $sp, 64
        jr $ra
