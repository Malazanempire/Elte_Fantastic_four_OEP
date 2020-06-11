A Duna vízállását különbözõ helyszíneken, különbözõ idõpontokban mérik, és az adatokat egy szöveges állományban rögzítik. Az állomány egy sora egy adott helyszínen egy adott napon mért adatokat tartalmazza: a helyszín nevét (szóközök nélküli sztring), a napi dátumot (YYYY.MM.DD alakú sztring), majd a méréseket. Minden mérés egy idõbélyegbõl (HH:MM alakú sztring) és egy vízállásból (egész szám cm-ben) áll. Az adatokat szóközök és/vagy tabulátorjelek választják el. Az állomány dátumok szerint, azon belül helyszínek szerint rendezett.
Példa az input fájl soraira:
Komárom  2019.06.03 08:30 630 12:30 640 20:30 670
Komárom  2019.06.04 08:30 680 12:30 665 20:30 645
Budapest 2019.06.05 08:30 730 12:30 740 20:30 755
Komárom  2019.06.05 08:30 630 12:30 615 20:30 595

Megfelelt szint (közepes): Válaszolja meg az alábbi kérdést: Volt-e olyan helyszín és nap (sor), amikor legalább ötször mértek vízállást, de az soha nem volt 400 cm-nél nagyobb?
Kiváló szint (jeles): Válaszolja meg az alábbi kérdést: Melyik napon mértek legkevesebbszer vízállást és hányszor, azokat a napokat figyelembe véve, amikor soha nem volt 400 cm-nél nagyobb a vízállás?

