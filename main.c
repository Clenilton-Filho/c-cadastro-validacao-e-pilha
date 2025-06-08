#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declarando o registro de cadastro
typedef struct INDIVIDUO{
    char nome[20];
    char CPF[11];
    int idade;
    float altura;
}INDIVIDUO;

//declarando o registro para os nós
typedef struct NO{
    INDIVIDUO dados_individuo;
    struct NO *proximo;
}NO;

//declarando o nó cabeça como NULL e global
NO *pilha_cadastros = NULL;

void imprimir(){
    NO *aux = pilha_cadastros;
    int contador = 1;
    
    printf("\nImprimindo dados");
    
    while (aux != NULL){
        printf("\nIndividuo %d\n",contador);
        printf("Nome: %s\n",aux->dados_individuo.nome);
        printf("CPF: %s\n",aux->dados_individuo.CPF);
        printf("Idade: %d\n",aux->dados_individuo.idade);
        printf("Altura: %.2f\n",aux->dados_individuo.altura);
        
        contador++;
        aux = aux->proximo;
    }
    
}

//função para adicionar itens à lista encadeada (pilha)
void empilhar(char nome[], char CPF[], int idade, float altura){
    //declarando o novo nó que será empilhado
    NO *novo_no = (NO*)malloc(sizeof(NO));
    
    //atribuindo os valores passados para os atributos do registro dados_individuo dentro do novo nó
    strcpy(novo_no->dados_individuo.nome, nome);
    strcpy(novo_no->dados_individuo.CPF, CPF);
    novo_no->dados_individuo.idade = idade;
    novo_no->dados_individuo.altura = altura;
    
    //o ponteiro dentro do novo nó aponta para o que antes era o nó cabeça
    novo_no->proximo = pilha_cadastros;
    
    
    //o novo nó agora será o nó cabeça
    pilha_cadastros = novo_no;
}

//função para remover o nó do início da lista encadeada (pilha)
void desempilhar(){
    //se a lista estiver vazia, apresenta uma mensagem e sai da função
    if (pilha_cadastros == NULL){
        printf("Lista vazia! Adicione pelo menos um nó para realizar essa operação.");
    }else{
        //declarando um nó auxiliar para guardar o endereço do nó cabeça atual
        NO *auxiliar = pilha_cadastros;
        
        //o nó cabeça atual é atualizado para o ponteiro dentro do nó cabeça
        pilha_cadastros = pilha_cadastros->proximo;
        
        //liberando a memória onde estava o nó cabeça anteriormente
        free(auxiliar);
    }
}

//ordenação por altura em bubblesort que troca somente os dados de indivíduo dentro dos nós
void ordenar_por_altura(){
    NO *auxiliar;
    INDIVIDUO dados_anterior;
    float valor_1;
    float valor_2;
    int trocou;
    
    //executa pelo menos uma vez e até que o bloco não tenha trocado os dados
    do{
        //'trocou' inicializa em cada loop como falso (0)
        trocou = 0;
        
        auxiliar = pilha_cadastros;
        while(auxiliar->proximo != NULL){
            //valor 1 recebe o atual
            valor_1 = auxiliar->dados_individuo.altura;
            
            //valor 2 recebe o próximo
            valor_2 = auxiliar->proximo->dados_individuo.altura;
            
            //se o atual for maior que o próximo, troca os dados dos nós e marca 'trocou' como verdadeiro (1)
            if(valor_1>valor_2){
                
                //os dados atuais são armazenados
                dados_anterior = auxiliar->dados_individuo;
                
                //os dados do atual vão ser trocados pelo do próximo
                auxiliar->dados_individuo = auxiliar->proximo->dados_individuo;
                auxiliar->proximo->dados_individuo = dados_anterior;
                trocou = 1;
            }
            //avança o atual
            auxiliar = auxiliar->proximo;
        }
        imprimir();
    }while(trocou == 1);
}

//ordenação por idade em selection sort que também só troca os dados dos nós
void ordenar_por_idade(){
    NO *auxiliar = pilha_cadastros;
    NO *auxiliar_2;
    NO *menor;
    INDIVIDUO dados_temporarios;
    
    //o while externo para quando o atual for nulo, que é quando a lista está ordenada (o loop interno já foi executado para cada posição da lista)
    while(auxiliar != NULL){
        
        //o menor vai ser sempre inicializado em cada loop externo como o atual 
        menor = auxiliar;
        
        //o auxiliar 2 é inicializado como o próximo do atual
        auxiliar_2 = auxiliar->proximo;
        
        //o while interno percorre a lista do atual até o último e tenta achar uma idade menor que a atual
        while(auxiliar_2 != NULL){
            
            //se achar, atualiza o valor de menor para o que está no auxiliar 2
            if(auxiliar_2->dados_individuo.idade<menor->dados_individuo.idade){
                menor = auxiliar_2;
            }
            
            //avança o auxiliar 2
            auxiliar_2 = auxiliar_2->proximo;
        }
        
        //troca os dados entre o menor que foi encontrado pelo loop interno e o atual
        dados_temporarios = auxiliar->dados_individuo;
        auxiliar->dados_individuo = menor->dados_individuo;
        menor->dados_individuo = dados_temporarios;
        
        
        imprimir();
        
        //avança o atual
        auxiliar = auxiliar->proximo;
    }
}

//função para migrar os cadastros do vetor para a lista encadeada
void migrar(INDIVIDUO *lista_individuos,int qtd_cadastros){
    for(int i = 0;i <= qtd_cadastros-1;i++){
        empilhar(
            lista_individuos[i].nome,
            lista_individuos[i].CPF,
            lista_individuos[i].idade,
            lista_individuos[i].altura);
    }
}

//funcao para validar CPF
int validar_CPF(char CPF[11]){
    
    //declarando variáveis
    char verificador_1;
    char verificador_2;
    int i2 = 10, i3 = 11;
    int resultado_multiplicacao = 0;
    int soma_1 = 0, soma_2 = 0;

    //obtendo o digito verificador 1
    for(int i = 0; i < 9; i++){
        if (i2 >= 2){
            resultado_multiplicacao = (CPF[i] - '0') * i2;
            soma_1 += resultado_multiplicacao;
            i2--;
        }
    }
    if(soma_1 % 11 < 2){
        verificador_1 = '0';
    }else{
        verificador_1 = '0' + (11 - soma_1 % 11);
    }
    
    //obtendo o digito verificador 2
    
    for(int i = 0; i < 10; i++){
        if (i3 > 2){
            resultado_multiplicacao = (CPF[i] - '0') * i3;
            soma_2 += resultado_multiplicacao;
            i3--;
        }else if(i3 == 2){
            soma_2 += (verificador_1 - '0') * 2;
        }
    }
    
    if(soma_2 % 11 < 2){
        verificador_2 = '0';
    }else{
        verificador_2 = '0' + (11 - soma_2 % 11);
    }
    
    //validando os dígitos verificadores
    if(CPF[9] == verificador_1 && CPF[10] == verificador_2){
        return 1;
    }else{
        return 0;
    }
}

//funcao para validar idade
int validar_idade(int idade){
    if(idade > 150 || idade < 0){
        return 0;
    }else{
        return 1;
    }
}

//funcao para validar altura
int validar_altura(float altura){
    if(altura > 3.0 || altura < 0.0){
        return 0;
    }else{
        return 1;
    }
}

//funcao para cadastro
INDIVIDUO cadastrar(int contador){
    //declarando a variável com o tipo do registro
    INDIVIDUO pessoa;
    
    //Recebendo e validando os dados
    printf("\nDigite os dados do individuo numero %d\n",contador);
    printf("Nome: ");
    scanf("%s",pessoa.nome);
    
    printf("CPF: ");
    scanf("%s",pessoa.CPF);
    
    while (validar_CPF(pessoa.CPF) != 1){
        printf("O CPF enviado é inválido! Digite novamente: ");
        scanf("%s",pessoa.CPF);
    }
    
    printf("Idade: ");
    scanf("%d", &pessoa.idade);
    
    while (validar_idade(pessoa.idade) != 1){
        printf("Idade inválida! Digite outra: ");
        scanf("%d",&pessoa.idade);
    }
    
    printf("Altura: ");
    scanf("%f", &pessoa.altura);
    
    while (validar_altura(pessoa.altura) != 1){
        printf("Altura inválida! Digite outra: ");
        scanf("%f",&pessoa.altura);
    }
    
    return pessoa;
        
}

int main(){
    //criando uma lista para os cadastros
    INDIVIDUO *lista_individuos;
    int qtd_cadastros = 0;
    
    //Apresentando o programa e recebendo a quantidade de cadastros
    printf("Bem vindo ao sistema de cadastros!\n");
    
    
    //só segue caso a quantidade de cadastros for maior que 0
    while (qtd_cadastros<=0){
        printf("Deseja cadastrar quantos individuos: ");
        scanf("%d",&qtd_cadastros);
        if(qtd_cadastros<=0){
            printf("Quantidade tem que ser maior que zero!\n");
        }
    }
    
    //alocando o tamanho recebido para o vetor dinâmico
    lista_individuos = (INDIVIDUO*)malloc(qtd_cadastros * sizeof(INDIVIDUO));
    
    //chamando a funcao de cadastro e passando a quantidade
    for(int i = 0;i < qtd_cadastros;i++){
        lista_individuos[i] = cadastrar(i+1);
    }
    
    //chamando a função para migrar os dados do vetor para a lista encadeada
    migrar(lista_individuos,qtd_cadastros);
    
    //liberando o espaço do vetor
    free(lista_individuos);
    
    desempilhar();
    empilhar("Ana","11111111111",31,1.67);
    empilhar("Pedro","22222222222",45,1.78);
    
    ordenar_por_altura();
    ordenar_por_idade();
    
    return 0;
}