

const mostrarGames = (data) => {
    let dadosHTML = '';
    let dadosGames = JSON.parse(data.target.response);

    localStorage.setItem('db_Games', data.target.response);
// id ->playtime
    for (let i = 0; i < dadosGames.results.length; i++) {
        let game = dadosGames.results[i];
        dadosHTML += `
            <div class="card col-xs-12 col-sm-6 col-md-3 col-lg-3 divListaGames">
                <img class="sizeimg card-img-top" src="${game.background_image}" alt="Game XPTO">
                <div class="card-body">
                    <h4 class="card-title">${game.name}</h4>
                    <p class="card-text"><b>Lançamento:</b> ${game.released}</p>
                    <p class="card-text"><b>Avaliação:</b> ${game.rating}</p>
                    <p class="card-text"><b>atualização:</b> ${game.updated}</p>
                    <a href="https://www.rawg.io/games/${game.id}" type="button" class="btn btn-sm btn-outline-secondary">Mais informações</a>
                </div>
            </div>
        `

    }
    document.getElementById('divListaGames').innerHTML = dadosHTML
}

const mostrarErro = (data) => {
    alert('Deu ERRO na requisição');
}


const inicializar = () => {

    let xhr = new XMLHttpRequest();
    let url = "https://api.rawg.io/api/games?key=258314e2df164affb49b0b2e2b46b967"
    xhr.onload = mostrarGames;
    xhr.onerror = mostrarErro;
    xhr.open('GET', url, true);
    xhr.send();
}

document.body.onload = inicializar;
//pesquisa
const pesquisar = () => {

    let input = document.querySelector("#txtBusca");
    let gameProcurado = input.value;
    let xhr = new XMLHttpRequest();
    let url = `https://api.rawg.io/api/games?key=258314e2df164affb49b0b2e2b46b967&search=${gameProcurado}`
    xhr.onload = mostrarGames;
    xhr.onerror = mostrarErro;
    xhr.open('GET', url, true);
    xhr.send();

    document.getElementById('gameProcurado').innerHTML = `
    <p class="gameProcurado"> Resultado da pesquisa para "${gameProcurado}" </p> `

}

const parametros = new URLSearchParams(location.search);
let id = parametros.get('id');

dadosGames = JSON.parse(localStorage.getItem('db_games'));

let idxGame = dadosGames.results.findIndex((elem) => elem.id == id);


if (idxGame >= 0) {

    let game = dadosGames.results[idxGame];


    //let generoApi1  = game.genre_ids[1];
    //let generoJson1 = generosGames.genres[1].id;
    //let nomeGenero1 = generosGames.genres[1].name;

    let nomeGenero = '';

    // mais informações
    document.getElementById('divDetalheGame').innerHTML = `
    <div class="divListaGames">
    <div class="col-xs-12 col-sm-12 col-md-12 col-lg-12">
      <h1 class="titulo-destaque">${game.name}</h1>
        <div class=" card-imagem-detalhe col-xs-4 col-sm-4 col-md-4 col-lg-4">
        <img class="sizeimg card-img-top" src="${game.background_image}" alt="Game XPTO">
        </div>
        <div class="card-detalhe col-xs-7 col-sm-7 col-md-7 col-lg-7>
            <p class="card-text"><b>Lançamento:</b> ${game.release_date}</p>
            <p class="card-text"><b>Avaliação: </b>${game.vote_average}</p>
            <p class="card-text"><b>Popularidade: </b>${game.popularity}</p>
            <p class="card-text"><b>Gênero(s): </b>${nomeGenero}</p>
            <p class="card-text"><b>Lançamento:</b> ${game.released}</p>
            <p class="card-text"><b>Sinopse: </b>${game.overview}</p>
            <a href="https://www.themoviedb.org/movie/${game.id}" type="button" class="btn btn-sm btn-outline-secondary">Mais informações</a>
            <a href="index.html" type="button" class="btn btn-sm btn-outline-secondary">Voltar</a>
        </div>
        </div>
    </div>
    </div>
`
}