import os
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin

# URL principal da disciplina de Estruturas de Dados
url_base = "https://www.inf.ufrgs.br/~dgbalreira/ed/"
pasta_destino = "Aulas_Estruturas_de_Dados"
os.makedirs(pasta_destino, exist_ok=True)

print("Acessando a página principal da disciplina...")
try:
    response = requests.get(url_base)
    response.raise_for_status()
except Exception as e:
    print(f"Erro ao acessar a página: {e}")
    exit()

soup = BeautifulSoup(response.text, 'html.parser')
links = soup.find_all('a')

print(f"Encontrados {len(links)} links na página. Baixando e renomeando materiais...\n")

for link in links:
    href = link.get('href')
    
    # Ignora âncoras na mesma página ou links de e-mail [cite: 51, 52]
    if not href or href.startswith('#') or href.startswith('mailto:'):
        continue
    
    url_arquivo = urljoin(url_base, href)
    
    # Só faz o download se o link pertencer à URL da disciplina
    if url_arquivo.startswith(url_base):
        
        # Limpa o caminho relativo
        caminho_relativo = url_arquivo.replace(url_base, "").split('?')[0].strip('/')
        
        # Pula se for a raiz principal
        if not caminho_relativo or caminho_relativo == "index.html":
            continue
            
        partes = caminho_relativo.split('/')
        
        # Lógica de renomeação baseada na estrutura do site
        if partes[-1] == "index.html":
            # Se o arquivo for index.html, ele pega o nome da pasta (ex: aula1a) e salva como aula1a.html
            nome_arquivo = f"{partes[-2]}.html" if len(partes) > 1 else "index.html"
        else:
            # Se for um arquivo extra (ex: zip de código em C), ele junta o nome da aula + nome do arquivo
            nome_arquivo = f"{partes[-2]}_{partes[-1]}" if len(partes) > 1 else partes[-1]
            
        caminho_local = os.path.join(pasta_destino, nome_arquivo)

        try:
            print(f"Salvando: {nome_arquivo} ...")
            arq_response = requests.get(url_arquivo)
            arq_response.raise_for_status()
            
            with open(caminho_local, 'wb') as f:
                f.write(arq_response.content)
        except Exception as e:
            print(f"  -> Erro ao baixar {caminho_relativo}: {e}")

# Salva o menu principal
with open(os.path.join(pasta_destino, "00_Menu_Principal.html"), 'wb') as f:
    f.write(response.content)

print(f"\nDownload concluído! Os arquivos das aulas foram salvos renomeados na pasta '{pasta_destino}'.")