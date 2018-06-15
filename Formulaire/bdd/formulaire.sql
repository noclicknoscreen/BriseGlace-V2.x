-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le :  ven. 15 juin 2018 à 11:20
-- Version du serveur :  5.7.19
-- Version de PHP :  5.6.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `formulaire`
--

-- --------------------------------------------------------

--
-- Structure de la table `enigme`
--

DROP TABLE IF EXISTS `enigme`;
CREATE TABLE IF NOT EXISTS `enigme` (
  `id` int(255) NOT NULL,
  `mot` varchar(50) NOT NULL,
  `theme` varchar(50) NOT NULL,
  `image0` varchar(200) NOT NULL,
  `imgcrop0` varchar(50) NOT NULL,
  `auteur0` varchar(50) NOT NULL,
  `date0` varchar(50) NOT NULL,
  `indice1` varchar(50) NOT NULL,
  `image1` varchar(200) NOT NULL,
  `imgcrop1` varchar(50) NOT NULL,
  `auteur1` varchar(50) NOT NULL,
  `date1` varchar(50) NOT NULL,
  `indice2` varchar(50) NOT NULL,
  `image2` varchar(200) NOT NULL,
  `imgcrop2` varchar(50) NOT NULL,
  `auteur2` varchar(50) NOT NULL,
  `date2` varchar(50) NOT NULL,
  `indice3` varchar(50) NOT NULL,
  `image3` varchar(200) NOT NULL,
  `imgcrop3` varchar(50) NOT NULL,
  `auteur3` varchar(50) NOT NULL,
  `date3` varchar(50) NOT NULL,
  `recompense` varchar(50) NOT NULL,
  `image4` varchar(200) NOT NULL,
  `imgcrop4` varchar(50) NOT NULL,
  `auteur4` varchar(50) NOT NULL,
  `date4` varchar(50) NOT NULL,
  `legende` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  UNIQUE KEY `id_2` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `enigme`
--

INSERT INTO `enigme` (`id`, `mot`, `theme`, `image0`, `imgcrop0`, `auteur0`, `date0`, `indice1`, `image1`, `imgcrop1`, `auteur1`, `date1`, `indice2`, `image2`, `imgcrop2`, `auteur2`, `date2`, `indice3`, `image3`, `imgcrop3`, `auteur3`, `date3`, `recompense`, `image4`, `imgcrop4`, `auteur4`, `date4`, `legende`) VALUES
(3, 'Couvent', 'lol4', 'https://c2.staticflickr.com/2/1398/556651580_168212776a_o.jpg', 'enigme/0003/image/image0-crop.jpg', 'fusion-of-horizons', '24 octobre 2002', 'Anish KapooR', 'https://upload.wikimedia.org/wikipedia/commons/9/99/Anish_Kapoor_at_the_Deutsche_Guggenheim_-_Berlin.jpg', 'enigme/0003/image/image1-crop.jpg', 'Torsodog', '10 juillet 2009', 'Iannis Xenakis', 'https://upload.wikimedia.org/wikipedia/commons/3/31/Iannis_Xenakis_1975.jpg', 'enigme/0003/image/image2-crop.jpg', 'Cyrus Sixguns', '7 June 2007', 'Le Corbusier', 'https://upload.wikimedia.org/wikipedia/commons/2/23/Le_Corbusier_1933.JPG', 'enigme/0003/image/image3-crop.jpg', 'Inconnu', '1 janvier 1933', 'Le couvent de La Tourette', 'https://upload.wikimedia.org/wikipedia/fr/f/f5/La_tourette-_arq._Le_Corbusier.jpg', 'enigme/0003/image/image4-crop.jpg', 'Alexandre Norman', '2007-09-16', 'Le couvent de La Tourette est une œuvre majeure de l\'architecte Le Corbusier. Les vitrages se veulent l\'adaptation de son œuvre Metastasis composée par Iannis Xenakis. L\'artiste plasticien Anish Kapoor fut l\'invité de la dernière biennale d\'art contemporain.'),
(2, 'gare444', 'lol3', 'https://d30y9cdsu7xlg0.cloudfront.net/png/1493048-200.png', 'enigme/0002/image/image0-crop.jpg', 'Andrea Caldarelli', 'Inconnu', 'Tunnel', 'https://upload.wikimedia.org/wikipedia/commons/f/f4/Lyon_Gorges_de_Loup_II.JPG', 'enigme/0002/image/image1-crop.jpg', 'Smiley.toerist', '21 mars 2009', 'Tram-train', 'https://upload.wikimedia.org/wikipedia/commons/2/2e/Tramtrain_in_l%27Arbresle_III.JPG', 'enigme/0002/image/image2-crop.jpg', 'Smiley.toerist', '18 octobre 2012', 'Horloger', 'https://c1.staticflickr.com/3/2853/11139667303_c0cc36843a_b.jpg', 'enigme/0002/image/image3-crop.jpg', 'Serge Barès', '29 novembre 2013', 'la gare Saint-Paul ', 'https://upload.wikimedia.org/wikipedia/commons/9/96/GareStPaulLyon.JPG', 'enigme/0002/image/image4-crop.jpg', 'Gotty', '28 septembre 2006', 'Chaque jour, 5 500 voyageurs passent par la gare Saint-Paul située dans le vieux Lyon ou fut tourné le film de Bertran Tavernier « L\'horloger de Saint Paul » en 1974. Le premier tram-train fut inauguré en septembre 2012.'),
(0, 'test1', 'lol1', 'https://upload.wikimedia.org/wikipedia/commons/2/20/Hugh_llewelyn_ZZAB5C_Ety_54005_%285727328869%29.jpg', 'enigme/0000/image/image0-crop.jpg', 'Oxyman', '29 mars 2009', 'Bugatti', 'https://upload.wikimedia.org/wikipedia/commons/thumb/c/c0/Bugatti_pr%C3%A9sidentiel%2C_Cit%C3%A9_du_train.jpg/1280px-Bugatti_pr%C3%A9sidentiel%2C_Cit%C3%A9_du_train.jpg', 'enigme/0000/image/image1-crop.jpg', 'Hugh Llewelyn', '29 mars 2009', 'Bibendum', 'https://upload.wikimedia.org/wikipedia/commons/8/88/Michelin_Poster_1898.jpg', 'enigme/0000/image/image2-crop.jpg', 'Ragilnih', '23 novembre 2017 ', 'Locomotive', 'https://upload.wikimedia.org/wikipedia/commons/6/6e/France_Paris_Champs_Elysees_Autorail_Picasso.JPG', 'enigme/0000/image/image3-crop.jpg', 'GIRAUD Patrick', '29 mai 2003', 'Micheline', 'https://upload.wikimedia.org/wikipedia/commons/8/8c/Lyon_St_Paul.JPG', 'enigme/0000/image/image4-crop.jpg', 'Smiley.toerist', '21 mars 2009', 'La « Micheline » est un autorail rapide équipé de roues spéciales munies de pneus brevetés appelés  « pneurail ». Elle construite par la société Michelin dans les années 1935. Bugatti réalisera également de tels véhicules de luxe dès 1932.'),
(1, 'Wagon-Lit', 'lol2', 'https://c2.staticflickr.com/6/5499/9772695506_c3e1aa39e8_b.jpg', 'enigme/0001/image/image0-crop.jpg', 'patrick janicek', '14 septembre 2013 ', 'L\'Orient Express', 'https://upload.wikimedia.org/wikipedia/commons/f/fd/L%27Orient_Express_vers_1930_%28c%29_wagons-lits_diffusion.jpg', 'enigme/0001/image/image1-crop.jpg', 'WLDiffusion', '2 septembre 2014', 'Georges Nagelmackers', 'https://upload.wikimedia.org/wikipedia/commons/b/b1/Georges_Nagelmackers_par_Nadar.jpg', 'enigme/0001/image/image2-crop.jpg', 'Nadar', '5 juillet 2011', 'Intercités', 'https://upload.wikimedia.org/wikipedia/commons/5/5f/L%27Intercit%C3%A9s_de_nuit_Paris_-_Austerlitz_Brian%C3%A7on_entre_en_gare_de_Brian%C3%A7on.jpg', 'enigme/0001/image/image3-crop.jpg', 'Damd071', '15 mars 2016', 'Compagnie internationale des Wagons-lits', 'https://upload.wikimedia.org/wikipedia/commons/4/4a/CIWL-Logo-bleu.jpg', 'enigme/0001/image/image4-crop.jpg', 'Tamorlan', '18 février 2014', 'La Compagnie internationale des Wagons-lits est une entreprise française d\'origine belge, fondée par Georges Nagelmackers en 1872. Intercités de nuit désigne, depuis 2012, le service de trains de nuit réguliers, proposé par la (SNCF), réalisé avec des voitures Corail.'),
(4, 'test7', 'lol5', 'https://c2.staticflickr.com/4/3787/20222411585_5cd12b9292_b.jpg', 'enigme/0004/image/image0-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3787/20222411585_5cd12b9292_b.jpg', 'enigme/0004/image/image1-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3787/20222411585_5cd12b9292_b.jpg', 'enigme/0004/image/image2-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3787/20222411585_5cd12b9292_b.jpg', 'enigme/0004/image/image3-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3787/20222411585_5cd12b9292_b.jpg', 'enigme/0004/image/image4-crop.jpg', 'v', 'v', 'v'),
(5, 'voir', 'lol6', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0005/image/image0-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0005/image/image1-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0005/image/image2-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0005/image/image3-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0005/image/image4-crop.jpg', 'v', 'v', 'v'),
(6, 'coucou', 'lol7', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0006/image/image0-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0006/image/image1-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0006/image/image2-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0006/image/image3-crop.jpg', 'v', 'v', 'v', 'https://c2.staticflickr.com/4/3278/2408815303_60ac9e80ef_b.jpg', 'enigme/0006/image/image4-crop.jpg', 'v', 'v', 'v');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
