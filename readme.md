# STT CSE Lab 6

### Jaskirat Singh Maskeen (23110146) and Aarsh Wankar (23110003)

## Repositories chosen:
- [alibaba/sentinel @ 4cad353d](https://github.com/alibaba/sentinel)

- [google/dagger @ c35a7990a](https://github.com/google/dagger)

- [google/guice @ c6839995f](https://github.com/google/guice)
 
## Analysis file: [main.ipynb](./main.ipynb)

## Tools chosen:

- [CodeQL](https://codeql.github.com/)

    ### CodeQL results:
    - [dagger (sarif)](./codeql_dagger-results.sarif) , [dagger-db](./dagger-db/)
    - [sentinel (sarif)](./codeql_sentinel-results.sarif) , [sentinel-db](./sentinel-db/)
    - [guice (sarif)](./codeql_guice-results.sarif) , [guice-db](./guice-db/)

- [Semgrep](https://semgrep.dev/)
    ### Semgrep results:
    - [dagger (sarif)](./semgrep_results_dagger.sarif)
    - [sentinel (sarif)](./semgrep_results_sentinel.sarif)
    - [guice (sarif)](./semgrep_results_guice.sarif)

- [Snyk](https://snyk.io/)

    ### Snyk results:
    - [dagger (sarif)](./snyk_results_dagger.sarif)
    - [sentinel (sarif)](./snyk_results_sentinel.sarif)
    - [guice (sarif)](./snyk_results_guice.sarif)