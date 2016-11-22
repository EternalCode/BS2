# Create portraits using imagemagick

# clean
rm -rf images/portraits
mkdir images/portraits

#crop images 
echo cropping image...
convert images/portrait_src.PNG -crop 43x42 images/portraits/unindexed_%03d.png
echo cropping complete

echo resizing cropped images...
convert images/portraits/unindexed_[0-9][0-9][0-9].png -background magenta -gravity center -extent 64x64 images/portraits/%03d.png
echo resizing complete

echo removing cropped files...
i=0
for file in images/portraits/unindexed_*.png
do
    i=$((i+1))
    rm -rf "$file"
done
echo removal complete

echo indexing images...
convert images/portraits/*.png -colors 16 images/portraits/face%03d.png
echo indexing complete

echo removing unindexed resized images...
for file in images/portraits/[0-9][0-9][0-9].png
do
    i=$((i+1))
    rm -rf "$file"
done
echo removal complete
echo removed "$i" files total.

# python script generates the header file
echo launching portraits header generation...
cd $PWD/scripts
python portraits.py
echo generation complete.


