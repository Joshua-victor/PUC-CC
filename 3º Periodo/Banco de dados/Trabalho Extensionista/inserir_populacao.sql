-- Populando a tabela Doador com valores genéricos
INSERT INTO Doador (CPF, Nome, Data_Nascimento, Telefone, Email, Endereco)
VALUES 
('000.000.000-00', 'Doador 1', '2000-01-01', '0000-0000', 'doador1@email.com', 'Endereço 1'),
('000.000.000-01', 'Doador 2', '2000-02-02', '0000-0001', 'doador2@email.com', 'Endereço 2');

-- Populando a tabela Doacao com valores genéricos
INSERT INTO Doacao (Data_Doacao, CPF_Doador)
VALUES 
(CURRENT_DATE, '000.000.000-00'),
(CURRENT_DATE, '000.000.000-01');

-- Populando a tabela Diretor com valores genéricos
INSERT INTO Diretor (CPF, Nome, Data_Nascimento, Email, Telefone)
VALUES 
('111.111.111-11', 'Diretor 1', '1970-01-01', 'diretor1@email.com', '1111-1111');

-- Populando a tabela Aprovacao com valores genéricos
INSERT INTO Aprovacao (ID_Doacao, CPF_Diretor, Data_Aprovacao)
VALUES 
(1, '111.111.111-11', CURRENT_DATE),
(2, '111.111.111-11', CURRENT_DATE);

-- Populando a tabela Fiel com valores genéricos
INSERT INTO Fiel (CPF, Nome, Data_Nascimento, Telefone, Email, Endereco)
VALUES 
('222.222.222-22', 'Fiel 1', '1990-01-01', '2222-2222', 'fiel1@email.com', 'Endereço Fiel 1');

-- Populando a tabela Entrega_Fiel com valores genéricos
INSERT INTO Entrega_Fiel (ID_Doacao, CPF_Fiel, Data_Entrega)
VALUES 
(1, '222.222.222-22', CURRENT_DATE);

-- Populando a tabela Voluntario com valores genéricos
INSERT INTO Voluntario (CPF, Nome, Data_Nascimento, Telefone, Email)
VALUES 
('333.333.333-33', 'Voluntário 1', '1985-01-01', '3333-3333', 'voluntario1@email.com');

-- Populando a tabela Beneficiario com valores genéricos
INSERT INTO Beneficiario (CPF, Nome, Data_Nascimento, Endereco, Num_Filhos)
VALUES 
('444.444.444-44', 'Beneficiário 1', '1980-01-01', 'Endereço Beneficiário 1', 2);

-- Populando a tabela Filho com valores genéricos
INSERT INTO Filho (CPF_Beneficiario, Nome, Data_Nascimento)
VALUES 
('444.444.444-44', 'Filho 1', '2010-01-01'),
('444.444.444-44', 'Filho 2', '2015-01-01');

-- Populando a tabela Entrega_Beneficiario com valores genéricos
INSERT INTO Entrega_Beneficiario (CPF_Voluntario, CPF_Beneficiario, Data_Entrega)
VALUES 
('333.333.333-33', '444.444.444-44', CURRENT_DATE);

-- Populando a tabela Item com valores genéricos
INSERT INTO Item (Nome, Descricao, Quantidade)
VALUES 
('Item 1', 'Descrição do item 1', 100),
('Item 2', 'Descrição do item 2', 200);

-- Populando a tabela Doacao_Item com valores genéricos
INSERT INTO Doacao_Item (ID_Doacao, ID_Item, Quantidade)
VALUES 
(1, 1, 10),
(1, 2, 20),
(2, 1, 15);

