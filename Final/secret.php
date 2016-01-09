<?php
    require("config.php");
    if(empty($_SESSION['user'])) 
    {
        header("Location: PLog.html");
        die("Redirecting to Index.php"); 
    }
?>

<!DOCTYPE html>
<html>
  <head>
    <title>BlackBird </title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/skeleton.css">
    <link rel="stylesheet" href="css/normalize.css">
    <link rel="stylesheet" href="css/men.css">
    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/functions.js"></script>
  </head>
  <body>
    <nav>
      <ul>
        <li><a href="Index.php">Login</a></li>
        <li><a href="Register.php">Registo</a></li>
        <li><a href="Secret.php">Area Cliente</a></li>
        <li><a href="about.html">Sobre Nos</a></li>
        <li><a href="women.html">Mulher</a></li>
        <li><a href="men.html">Homem</a></li>
        <li><a href="index.html">Home</a></li>
      </ul>
    </nav>
    <header class="background">
      <div class="logo"></div>
    </header>
    <article>
      <hr>
      <h1>Area de Cliente</h1>
      <hr>
      <a href="logout.php">Estás logado , clica aqui para fazer log out</a>
      <form action="mailto:blackbird@blackbird.com" method="GET">
        <div class="row">
          <div class="six columns">
            <label for="exampleEmailInput">O teu email</label>
            <input class="u-full-width" placeholder="oteumail@mail.com" id="exampleEmailInput" type="email">
          </div>
            <div class="six columns">
              <label for="exampleMessage">Cartao de cidadão</label>
          <textarea class="u-full-width" placeholder="1234567 NF3" id="exampleMessage"></textarea>
              </select>
            </div>
            <div class="six columns">
            <label for="exampleMessage">Sexo</label>
          <textarea class="u-full-width" placeholder="M/F" id="exampleMessage"></textarea>
            </div>
           <div class="six columns">
            <label for="exampleMessage">Idade</label>
          <input class="u-full-width" placeholder="23" id="exampleMessage" type="number"></input>
            </div>
             <div class="six columns">
            <label for="exampleMessage">Morada</label>
          <textarea class="u-full-width" placeholder="Rua dos combatentes da grande guerra , 307, 3030-181" id="exampleMessage"></textarea>
            </div>
          </div>
          <br>
          <label for="exampleMessage">Mensagem</label>
          <textarea class="u-full-width" placeholder="Deixe aqui o seu comentário / Questão!" id="exampleMessage"></textarea>
          <input class="button-primary" value="Enviar" type="submit">
      </form>
    </article>
    <footer>
      <div class="row footer">
        <div class="columns three"><strong>ENCONTRA-NOS:</strong>
          <ul>
            <li><a href="">Twitter</a></li>
            <li><a href="">Facebook</a></li>
            <li><a href="">Pinterest</a></li>
          </ul>
        </div>
        <div class="columns three"><strong>FEITO POR</strong>
          <ul>
            <li>Miguel Dias</li>
            <li>Gabriel Silva</li>
          </ul>
        </div>
      </div>
    </footer>
  </html>