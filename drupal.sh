echo "fetching changes from orocos.org:"
rsync -Ciuavz --exclude="files/css" --exclude="stable" --exclude="devel" --exclude="rtt" --exclude="ocl" --exclude="kdl" --exclude="bfl" bruyninckxh2@www.orocos.org:www.orocos.org/ drupal/ 
echo "sending changes to orocos.org:"
rsync -Ciuavz drupal/ bruyninckxh2@www.orocos.org:www.orocos.org/
echo "Done."
