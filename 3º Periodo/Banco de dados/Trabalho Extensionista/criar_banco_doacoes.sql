-- Tabela Doador: Armazena os dados dos doadores
CREATE TABLE Doador (
    CPF VARCHAR(14) NOT NULL, 
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Telefone VARCHAR(20),
    Email VARCHAR(100),
    Endereco VARCHAR(200),
    PRIMARY KEY (CPF)
);

COMMENT ON TABLE Doador IS 'Tabela que armazena os dados dos doadores.';

-- Tabela Doacao: Armazena as doações realizadas pelos doadores
CREATE TABLE Doacao (
    ID_Doacao INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    Data_Doacao DATE NOT NULL,
    CPF_Doador VARCHAR(14) NOT NULL,
    FOREIGN KEY (CPF_Doador) REFERENCES Doador(CPF) ON DELETE CASCADE
);

COMMENT ON TABLE Doacao IS 'Tabela que armazena as doações realizadas pelos doadores.';

CREATE INDEX index_doacao_cpf_doador ON Doacao (CPF_Doador);

-- Tabela Diretor: Armazena os dados dos diretores responsáveis por aprovar doações
CREATE TABLE Diretor (
    CPF VARCHAR(14) NOT NULL,
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Email VARCHAR(100),
    Telefone VARCHAR(20),
    PRIMARY KEY (CPF)
);

COMMENT ON TABLE Diretor IS 'Tabela que armazena os dados dos diretores responsáveis por aprovar doações.';

-- Tabela Aprovacao: Registra as aprovações de doações realizadas pelos diretores
CREATE TABLE Aprovacao (
    ID_Aprovacao INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    ID_Doacao INT NOT NULL,
    CPF_Diretor VARCHAR(14) NOT NULL,
    Data_Aprovacao DATE NOT NULL,
    FOREIGN KEY (ID_Doacao) REFERENCES Doacao(ID_Doacao) ON DELETE CASCADE,
    FOREIGN KEY (CPF_Diretor) REFERENCES Diretor(CPF) ON DELETE CASCADE
);

COMMENT ON TABLE Aprovacao IS 'Tabela que registra as aprovações de doações realizadas pelos diretores.';

-- Tabela Fiel: Armazena os dados dos fiéis que podem receber doações
CREATE TABLE Fiel (
    CPF VARCHAR(14) NOT NULL,
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Telefone VARCHAR(20),
    Email VARCHAR(100),
    Endereco VARCHAR(200),
    PRIMARY KEY (CPF)
);

COMMENT ON TABLE Fiel IS 'Tabela que armazena os dados dos fiéis que podem receber doações.';

-- Tabela Entrega_Fiel: Registra as entregas de doações aos fiéis
CREATE TABLE Entrega_Fiel (
    ID_Entrega INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    ID_Doacao INT NOT NULL,
    CPF_Fiel VARCHAR(14) NOT NULL,
    Data_Entrega DATE NOT NULL,
    FOREIGN KEY (ID_Doacao) REFERENCES Doacao(ID_Doacao) ON DELETE CASCADE,
    FOREIGN KEY (CPF_Fiel) REFERENCES Fiel(CPF) ON DELETE CASCADE
);

COMMENT ON TABLE Entrega_Fiel IS 'Tabela que registra as entregas de doações aos fiéis.';

CREATE INDEX index_entrega_fiel_cpf_fiel ON Entrega_Fiel (CPF_Fiel);

-- Tabela Voluntario: Armazena os dados dos voluntários que realizam entregas
CREATE TABLE Voluntario (
    CPF VARCHAR(14) NOT NULL,
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Telefone VARCHAR(20),
    Email VARCHAR(100),
    PRIMARY KEY (CPF)
);

COMMENT ON TABLE Voluntario IS 'Tabela que armazena os dados dos voluntários que realizam entregas.';

-- Tabela Beneficiario: Armazena os dados dos beneficiários que recebem doações
CREATE TABLE Beneficiario (
    CPF VARCHAR(14) NOT NULL,
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Endereco VARCHAR(200),
    Num_Filhos INT,
    PRIMARY KEY (CPF)
);

COMMENT ON TABLE Beneficiario IS 'Tabela que armazena os dados dos beneficiários que recebem doações.';

-- Tabela Filho: Armazena os filhos dos beneficiários
CREATE TABLE Filho (
    CPF_Beneficiario VARCHAR(14) NOT NULL,
    Nome VARCHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    PRIMARY KEY (CPF_Beneficiario, Nome),
    FOREIGN KEY (CPF_Beneficiario) REFERENCES Beneficiario(CPF) ON DELETE CASCADE
);

COMMENT ON TABLE Filho IS 'Tabela que armazena os filhos dos beneficiários.';

-- Tabela Entrega_Beneficiario: Registra as entregas realizadas por voluntários aos beneficiários
CREATE TABLE Entrega_Beneficiario (
    ID_Entrega INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    CPF_Voluntario VARCHAR(14) NOT NULL,
    CPF_Beneficiario VARCHAR(14) NOT NULL,
    Data_Entrega DATE NOT NULL,
    FOREIGN KEY (CPF_Voluntario) REFERENCES Voluntario(CPF) ON DELETE CASCADE,
    FOREIGN KEY (CPF_Beneficiario) REFERENCES Beneficiario(CPF) ON DELETE CASCADE
);

COMMENT ON TABLE Entrega_Beneficiario IS 'Tabela que registra as entregas realizadas por voluntários aos beneficiários.';

CREATE INDEX index_entrega_beneficiario_cpf_beneficiario ON Entrega_Beneficiario (CPF_Beneficiario);

-- Tabela Item: Armazena os itens disponíveis para doação
CREATE TABLE Item (
    ID_Item INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    Nome VARCHAR(100) NOT NULL,
    Descricao VARCHAR(200),
    Quantidade INT NOT NULL CHECK (Quantidade > 0)
);

COMMENT ON TABLE Item IS 'Tabela que armazena os itens disponíveis para doação.';

-- Tabela Doacao_Item: Relaciona os itens às doações realizadas
CREATE TABLE Doacao_Item (
    ID_Doacao INT NOT NULL,
    ID_Item INT NOT NULL,
    Quantidade INT NOT NULL CHECK (Quantidade > 0),
    PRIMARY KEY (ID_Doacao, ID_Item),
    FOREIGN KEY (ID_Doacao) REFERENCES Doacao(ID_Doacao) ON DELETE CASCADE,
    FOREIGN KEY (ID_Item) REFERENCES Item(ID_Item) ON DELETE CASCADE
);

COMMENT ON TABLE Doacao_Item IS 'Tabela que relaciona os itens às doações realizadas.';
