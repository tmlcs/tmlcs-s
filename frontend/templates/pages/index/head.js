// Define el contenido de la página de inicio
function HeadMeta() {
    const Metadata = `
	<meta name="application-name" content="TechMaLoGiC Web 1.0">
	<meta name="author" content="TMLCS MVP">
	<meta name="keywords" content="TechMaLoGiC Web, TechMaLoGiC INST, TechMaLoGiC University, TechMaLoGiC Collections">
	<meta name="description" content="TechMaLoGiC Network">
	<title>TMLCS COLLECTIONS</title>
	<link rel="stylesheet" type="text/css" href="/templates/static/normalize.css" media="all">
	<link rel="preconnect" href="https://fonts.gstatic.com">
	<link href="https://fonts.googleapis.com/css2?family=Lobster&display=swap" rel="stylesheet">
	<script src="https://kit.fontawesome.com/8a6bae6500.js" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
    `;
    document.getElementById('MetaData').innerHTML = Metadata;
}

// Llama a la función para mostrar la página de inicio cuando se carga la página
HeadMeta();
