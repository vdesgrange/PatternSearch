UML=$(./src/ressources/graph/*.uml)
PNG=$(UML:.uml=.png)

all: $(PNG) texDoc mvdoc pseudoclean

%.png: %.uml
	java -jar plantuml.jar $<

texDoc:
	cd src; /Library/TeX/texbin/pdflatex rapport.tex;
	cd src; /Library/TeX/texbin/pdflatex rapport.tex;

mvdoc:
	mv src/*.pdf doc/

pseudoclean:
	rm -rf src/*.log src/*.aux src/*.toc src/*.out src/*blx.bib src/*.run.xml src/*.nlo src/*.nls src/*.ilg src/*.lof

clean: pseudoclean
	rm -rf doc/*.pdf
