# 📡 Minitalk

O **Minitalk** é um projeto da 42 School cujo objetivo é implementar um sistema de comunicação entre dois processos — um cliente e um servidor — usando apenas sinais UNIX (`SIGUSR1` e `SIGUSR2`). A comunicação é feita bit a bit, simulando uma transmissão assíncrona de mensagens.

---

## 🧠 Conceito

O servidor escuta sinais enviados pelo cliente. Cada caractere da mensagem é convertido em bits e enviado como uma sequência de sinais. Ao final, o cliente envia um caractere `\0` para indicar que a transmissão foi concluída.

---

## 🗂️ Estrutura

- `server.c`: inicia o servidor e imprime mensagens recebidas.
- `client.c`: envia uma string como argumento para o servidor usando sinais.
- `minitalk.h`: header com includes necessários.
- `Makefile`: compila os dois binários (`server` e `client`).
- `libft`: dependência externa utilizada (funções auxiliares como `ft_putendl_fd`).

---

## ⚙️ Compilação

Execute:

```bash
make
```

Isso irá gerar os binários:

- `server`
- `client`

Para limpar os objetos e binários:

```bash
make clean
make fclean
make re
```

---

## 🧪 Como usar

1. Inicie o servidor em um terminal:

```bash
./server
PID[12345]
```

2. Em outro terminal, envie uma mensagem com o `client`:

```bash
./client 12345 "Mensagem secreta"
```

O cliente envia a mensagem bit a bit para o servidor, que imprime a mensagem no terminal.

---

## 📌 Detalhes técnicos

- Cada bit é enviado como `SIGUSR1` (bit 1) ou `SIGUSR2` (bit 0)
- O cliente espera a confirmação (`SIGUSR1`) antes de enviar o próximo bit
- A mensagem termina com um caractere nulo (`\0`)
- O servidor responde com `SIGUSR2` ao fim da recepção

---

## ⚠️ Tratamento de erros

- Verificação do número de argumentos
- Falha ao enviar sinais (`kill`)
- Falha ao registrar handlers de sinal

---

## 📜 Licença

Distribuído sob os termos do arquivo [`LICENSE`](./LICENSE).

---

> Projeto desenvolvido por **[ngomes-t@student.42sp.org.br](mailto:ngomes-t@student.42sp.org.br)** como parte do currículo da 42 São Paulo
