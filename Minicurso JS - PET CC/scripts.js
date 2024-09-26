    class Pessoa{
        constructor(nome, curso, idade){
            this.nome = nome;
            this.curso = curso;
            this.idade = idade;
        }
    }

    const pessoas = [];

    function adicionar_aluno(){
        const nome = document.getElementById('input-nome').value;
        const curso = document.getElementById('input-curso').value;
        const idade = document.getElementById('input-idade').value;

        const pessoa = new Pessoa(nome, curso, idade);
        pessoas.push(pessoa);

        atualizar_lista();
    }

    function atualizar_lista(){
        const lista = document.getElementById("lista_alunos");
        lista.innerHTML = '';
        pessoas.forEach(pessoa => {
            const item = document.createElement('li');
            item.textContent = `Nome: ${pessoa.nome} | Curso: ${pessoa.curso} | Idade: ${pessoa.idade} anos`;
            
            const btn_remove = document.createElement('button');
            btn_remove.textContent = 'Remover';
            
            btn_remove.addEventListener('click', () => {
                remover_aluno(pessoa);
            });
            item.appendChild(btn_remove);
            lista.appendChild(item);
        });
    }

    function remover_aluno(pessoa){
        const indice = pessoas.indexOf(pessoa);
        
        if (indice !== -1){
          pessoas.splice(indice, 1);
          atualizar_lista();
          console.log("Aluno removido com sucesso! ");
        }
    }
