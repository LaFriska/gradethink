echo "Compiling gradethink..."
make clean >/dev/null
make >/dev/null
echo "Deploying binary in ./arm64/"
cp gradethink arm64
echo "Deploying binary in /usr/local/bin/"
cp gradethink /usr/local/bin/
make clean >/dev/null