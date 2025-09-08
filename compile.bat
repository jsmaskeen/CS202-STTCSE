
set MAIN=assessment2

REM First LaTeX pass
pdflatex -interaction=nonstopmode %MAIN%.tex

REM Run bibtex on each aux file (main + chapters)
for %%f in (chapters\*.aux %MAIN%.aux) do (
    echo Running bibtex on %%~nf
    bibtex %%~nf
)

REM Two more LaTeX passes
pdflatex -interaction=nonstopmode %MAIN%.tex
pdflatex -interaction=nonstopmode %MAIN%.tex

echo :3 Compilation finished. Output: %MAIN%.pdf

