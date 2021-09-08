# SACFA
###### Soldat Admin Client For Android  
Still in development, don't use it in competitive servers.  
It's incomplete, there's no notification feature, in case a player says !admin or another keyword, there's no way to close a single tab, you can only close all the tabs at once, there's a subwindow that shows the players, but it's not fully functional, so you can't use the players list to perform any action like making a player an admin or kicking a player. You can connect to a server but there's no disconnect button. There's no way you can set your admin name, it's hardcoded as "Hardcoded User".  
#### What SACFA can do:(bweare that by the time you read this, this list might be outdated)  
* It can create tabs to manage more than a server at the same time.  
* It saves the server's ip, port and password everytime the user clicks on the button.  
* It can reply to /clientlist requests from other admin clients and from scripts.  
* It can parse the REFRESHX packet,(only REFRESHX, REFRESH doesn't work)  

Part of the REFRESHX data might be shown on the Players subwindow, that is opened when the user clicks on the button at the bottom of the screen.     
I will only make a release when the basic features are all implemented, and after i test it for at least 50 hours.  
There might be apks available from download that came from automated builds on github Actions, inside a zip folder.  
Currently SACFA generates some logs on the folder Android/data/org.qproject.example.SACFA
### License
GPL-2.0 everything except the third party stuff that comes with their own license, in this case there will be a license file on a subfolder. Currently only inih(https://github.com/jtilly/inih) has another license, it's in a subfolder.
