#!/usr/bin/env bash
rostrojan="../bin/Debug/ROStrojan"

echo ">>>Archivo: Busca el archivo a partir del directorio actual. Una vez localizado muestra su localización relativa."
${rostrojan} -b secrets.txt

echo ">>>Directorio: Muestra el contenido del directorio especificado, incluyendo los directorios que contiene éste."
${rostrojan} -d .

echo ">>>Archivo: Muestra en pantalla el contenido de un archivo, bloqueando para lectura tod0 el archivo antes de comenzar a mostrar, y desbloqueándolo antes de terminar."
${rostrojan} -a lista-barcenas.txt

echo ">>>Entorno:"
# Borrar entorno si existe
file="../entorno.dat"
if [ -f ${file} ] ; then
    rm ${file}
fi

echo "Crear fichero de entorno y sección s1, s2 y s3"
${rostrojan} -e s1

${rostrojan} -e s2

${rostrojan} -e s3

echo "Anadir variables a las secciones"
${rostrojan} -e s1 var11 11

${rostrojan} -e s2 var21 21

${rostrojan} -e s3 var31 31

${rostrojan} -e s1 var12 12

${rostrojan} -e s2 var22 22

${rostrojan} -e s3 var32 32

echo "Listar entorno"
${rostrojan} -e

echo "Listar sección s1"
${rostrojan} -e s1

echo "Ver variable var12"
${rostrojan} -e s1 var12

echo "Modificar variable var12 a 999"
${rostrojan} -e s1 var12 999

echo "Ver variable var12"
${rostrojan} -e s1 var12

echo ">>>Usuarios: Bloqueará para lectura el archivo /etc/passwd y buscará el uid visualizando el nombre de usuario, el nombre del grupo y su directorio personal. Si no se especifica nada se mostrarán todos los usuarios, grupo y directorio personal."
${rostrojan} -u

echo "Usuario UID=0 (root)"
${rostrojan} -u 0

echo ">>>Grupos: Bloqueará para lectura el archivo /etc/group y lo recorrerá visualizando el nombre del grupo."
${rostrojan} -g

echo "Grupo GID=4 (adm)"
${rostrojan} -g 4

echo ">>>Muestra el usuario actual."
${rostrojan} -U

echo ">>>Muestra el nombre del equipo"
${rostrojan} -h

echo ">>>Muestra el sistema operativo."
${rostrojan} -s

echo ">>>Muestra la versión del kernel."
${rostrojan} -k

echo ">>>Muestra la dirección IP."
${rostrojan} -n