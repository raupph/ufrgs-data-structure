import os

# Nome da pasta onde estão os arquivos baixados
pasta = "Aulas_Estruturas_de_Dados"

# Verifica se a pasta realmente existe no local onde o script está rodando
if not os.path.exists(pasta):
    print(f"Erro: A pasta '{pasta}' não foi encontrada.")
    print("Certifique-se de rodar este script no mesmo local onde a pasta está.")
    exit()

contador = 0
extensoes_para_mudar = ('.html', '.c', '.h')

print(f"Analisando os arquivos na pasta '{pasta}'...\n")

for nome_arquivo in os.listdir(pasta):
    # Verifica se o arquivo termina com alguma das extensões alvo
    if nome_arquivo.endswith(extensoes_para_mudar):
        caminho_antigo = os.path.join(pasta, nome_arquivo)
        
        # Separa o nome do arquivo da extensão atual e adiciona .txt
        nome_sem_extensao = os.path.splitext(nome_arquivo)[0]
        novo_nome = f"{nome_sem_extensao}.txt"
        caminho_novo = os.path.join(pasta, novo_nome)
        
        try:
            os.rename(caminho_antigo, caminho_novo)
            print(f"Renomeado: {nome_arquivo}  ->  {novo_nome}")
            contador += 1
        except Exception as e:
            print(f"Erro ao renomear {nome_arquivo}: {e}")

print(f"\nPronto! {contador} arquivos foram transformados em .txt com sucesso.")