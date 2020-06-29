# Geoloc

## Goal 
Realize an application allowing the study, the modification of geolocation trace.
<br/>
<b><i>The C language was imposed on this project. It's not the best nor the easiest language choice. Even if it's possible to 'emulate' the behaviour of an object-oriented language, it would have been preferable, and easier to use C++, especially when manipulating graphics objects.</i></b>

## Privacy
Data are recovered from different people whose anonymity is a priority. This tool offer the possiblity to erase from logs files, unwanted position.

## Log data treatment
<u>For each log :</u>
  - Import the file containing the traces-model the different points (one line of the log which contains a date and a position in the form of longitude and latitude)
  - Each point is added to a double chained list, ready to be treated.
  - Areas of interest are discovered using a data partitioning algorithm DBSCAN (more information at https://en.wikipedia.org/wiki/DBSCAN ) 
  
## Adresse database treatment
In order to characterize the centres of interest, we use an IGN address base of region Cher (France, 18)
The point corresponding to the centre of interest is compared to the nearest address to find out the address of the centre of interest in question. <br/>
<br/>
<i>The database if a 23Mo CSV file, in order to improve the search operations in this base, the file is splitted in multiple file, and indexed. You can find the code indexing the base at /index </i>

## Data Display
This project's UI was realized using CSFML ( C bind of SFML) : 
  - interface that offers modules to facilitate the development of games or multimedia applications-easier to display the       map, points and different centers 
