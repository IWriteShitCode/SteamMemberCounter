# SteamMemberCounter
Counts the number of steam members in groups of games

----------

Number of followers for each of the publicly available games on Steam

The follower count is the number of people that have pressed: “Follow” on a game. This is not the number of wishlists, wishlists are more common than follows (A little more than double the number of followers, but this varies from game to game and genre to genre).

Wishlists disappear after the user purchased the game. Follows stay until the user unfollows.

There’s some kind of correlation between follows and sales (obviously), but it’s probably varied to get any usable result.

This list was done during 13 → 15 january.

The code is hard-coded as fuck. There’s no libraries. I tried a bunch of them, but then I found: URLOpenBlockingStream(), which is just plain awesome!

NOTE: Some games can be missing, since they don't use their STEAM-APP-ID as the group adress. So if there's a game missing, this is probably why. 

S
