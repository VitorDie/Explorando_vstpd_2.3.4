# Explorando_vstpd_2.3.4

  Esse script tem como objetivo explorar o backdoor existente no serviço, vstpd 2.3.4, presente no Metasploitable2, em outras maquinas vulneráveis, e também em alguns ctfs de nível fácil.
  O script consiste em conectar no host pela porta ftp(geralmente 21), enviar "USER user:)"; "PASS senha", após isso se conectar na porta 6200, e então interagir com uma shell bem primitiva.
  O que ativa a porta 6200 é o sorriso ":)" no final da requisição USER.
  Antes de usar esse exploit, é necessário alterar o ip do alvo no método socket_connect, em "remote.sin_addr.s_addr = inet_addr("192.168.0.120")". Coloque no lugar de "192.168.0.120" o ip do seu alvo.
