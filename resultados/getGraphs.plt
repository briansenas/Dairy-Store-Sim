set encoding utf8
set terminal png size 1280, 720 enhanced font "Alegreya,18"
# set terminal pngcairo size 1280, 720 enhanced color dashed font "Alegreya, 14" \
# set terminal pdfcairo enhanced color dashed font "Alegreya, 14" \
# set terminal epslatex color colortext
# rounded size 16 cm, 9.6 cm
set print "-"
set key on
set key bottom right
set auto
set grid
set size 1,1
set macro

# Standard border
set style line 11 lc rgb '#808080' lt 1 lw 3
set border 0 back ls 11
set tics out nomirror

# Standard grid
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
# unset grid

set style line 1 lc rgb '#E41A1C' pt 1 ps 1 lt 1 lw 1 # red
set style line 2 lc rgb '#377EB8' pt 6 ps 1 lt 1 lw 1 # blue
set style line 3 lc rgb '#4DAF4A' pt 2 ps 1 lt 1 lw 1 # green
set style line 4 lc rgb '#984EA3' pt 3 ps 1 lt 1 lw 1 # purple
set style line 5 lc rgb '#FF7F00' pt 4 ps 1 lt 1 lw 1 # orange
set style line 6 lc rgb '#FFFF33' pt 5 ps 1 lt 1 lw 1 # yellow
set style line 7 lc rgb '#A65628' pt 7 ps 1 lt 1 lw 1 # brown
set style line 8 lc rgb '#F781BF' pt 8 ps 1 lt 1 lw 1 # pink

file_exists(file ) = system("[ -f '".file."' ] && echo '1' || echo '0'") + 0

set palette defined ( 0 "red", 1 "green")
set cbrange[0:1]
# color(y) = y >= 0 ? (255*65535) : (255*255)


dir = "graphs/".apartado
system "mkdir ".dir

# https://stackoverflow.com/questions/37674787/gnuplot-get-value-of-a-particular-data-in-a-datafile-with-or-without-using-sta
getValue(row,col,filename) = system('awk ''{if (NR == '.row.') print $'.col.'}'' '.filename.'')

set key inside
set key top right

# lines = floor(system("wc -l media1-120-0-40.txt"))
outname = dir."/Dias.png"
set output outname
set title "Días Donados e Insuficientes"
plot filename i 0 u :1 w lp ls 2 title "Dias donados", \
filename i 0 u :3 w lp ls 1 title "Dias insuficientes"

outname = dir."/Cantidades.png"
set output outname
set title "Cantidades Donadas y Ventas Pérdidas"
plot filename i 0 u :2 w lp ls 2 title "Cantidad Donada", \
filename i 0 u :4 w lp ls 1 title "Cantidad Ventas Pérdidas"

outname = dir."/Ganancia.png"
set output outname
set title "Ganancia Obtenida"
plot filename i 0 u :5 w lp ls 3 title "Ganacia Obtenida"
