Algoritmo "O_menor_valor"

var
    c1, c2: inteiro

Inicio
// Seção de Comandos
Escreva ("Entre com as variaveis(0 para parar): ")
    Leia (c1)
    repita
          Leia(c2)
          se c2 <> 0 entao
             se c1 > c2 entao
                c1 <- c2
             fimse
          fimse
    ate c2 = 0
    escreva("O menor valor é: ", c1)
Fimalgoritmo
