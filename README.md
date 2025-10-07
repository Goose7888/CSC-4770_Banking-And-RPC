# Distributed Banking System Assignment

## Introduction

In this lab, students will design and implement middleware for a
distributed banking system using Remote Procedure Calls (RPC). The goal
is to simulate a virtual banking environment where clients interact with
multiple bank services through a unified interface.

## Learning Objective

-   Understand the principles of RPC in distributed systems.
-   Design middleware that integrates multiple services.
-   Implement client-server communication using RPC.
-   Use SQLite3 for persistent storage in distributed services.

## Project Overview

You will implement a distributed banking system with the following
architecture:

<img width="904" height="382" alt="image" src="https://github.com/user-attachments/assets/0925a5de-d540-40b1-94d0-73077476a7c7" />

-   A **client** can perform operations: `credit`, `debit`, and
    `transfer`.  Client use RPC to communication with the middleware.
-   A **virtual bank middleware** maps account numbers to banks and
    delegates operations to the correct bank.  Middleware acts as an RPC
    server to accept service calls from the client, and acts and an RPC
    client to request services from the bank.
-   **BANK1** and **BANK2** are individual RPC servers managing their
    own accounts.

<img width="797" height="631" alt="image" src="https://github.com/user-attachments/assets/e404c02d-bd1a-405f-a98f-7257871e8575" />


Note that for the purposes of this assignment, the Bank should never let
an account go negative. In such a case, the bank should return an error
value indicating that the transfer, credit, or debit is not allowed.

## Platform

-   Use the Course provided Debian VM (VirtualBox version for Intel
    users, UTM version for Apple Silicon users).

-   Install RPC tools: `sudo apt-get install rpcbind`\

-   Install SQLite3:\

        sudo apt install sqlite3
        sudo apt install libsqlite3-dev

-   A tutorial for programming SQLite3 in C++ follows: [[sqlite3
    tutorial](/d2l/common/dialogs/quickLink/quickLink.d2l?ou=10238929&type=coursefile&fileId=sqlite3_tutorial.html){rel="noopener"
    target="_blank"}[]{.panorama-alternative-formats-button-container
    title="Alternative Formats for sqlite3_tutorial.html"
    style="width: 20px !important; height: 20px !important; margin-left: 5px;"}]{.pano-wrapper-div
    style="line-height: 1.9;" accessibility_injected="true"}

    ::: {.panorama-alternative-formats-button tabindex="0" role="button" panorama-document-type="file" style="width: 20px; height: 20px;" aria-label="Alternative Formats for sqlite3_tutorial.html"}
    ![](data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMjAiIGhlaWdodD0iMjAiIGFyaWEtbGFiZWw9IkFjY2Vzc2liaWxpdHkgU2NvcmUgSWNvbiIgdmlld2JveD0iMCAwIDIwIDIwIiBmaWxsPSJub25lIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPgogICAgICAgICAgICA8Y2lyY2xlIGN4PSI5LjU5MDU2IiBjeT0iOS44MTUzMiIgcj0iOC42NDcyNiIgZmlsbD0id2hpdGUiPjwvY2lyY2xlPgogICAgICAgICAgICA8ZyBjbGlwLXBhdGg9InVybCgjY2xpcDBfMjE4XzkyOCkiPgogICAgICAgICAgICAgICAgPHBhdGggZD0iTTkuOTk2ODMgMC4yMjQ2ODJDMTUuMzk1IDAuMjIzMDkxIDE5Ljc3MzcgNC41OTg1OSAxOS43NzUzIDkuOTk2NzhDMTkuNzc2OSAxNS4zOTUgMTUuNDAxNCAxOS43NzM3IDEwLjAwMzIgMTkuNzc1MkM0LjYwMzQxIDE5Ljc3NjggMC4yMjYzMjIgMTUuNDAxMyAwLjIyNDczMSAxMC4wMDMxQzAuMjI0NzMxIDcuNDA5MDIgMS4yNTM3OSA0LjkyMTQ2IDMuMDg3NjUgMy4wODc2QzQuOTE4MzMgMS4yNTIxNSA3LjQwNDMgMC4yMjE1MDEgOS45OTY4MyAwLjIyNDY4MlpNOS45MzQ4IDEyLjAyMzFMOC41MTEyOSAxNS45NTY0QzguNDQxMzEgMTYuMTU1MiA4LjI5MzM5IDE2LjMxNzUgOC4xMDA5NCAxNi40MDY1QzcuNzAzMzEgMTYuNTkyNiA3LjIyOTM0IDE2LjQyMjQgNy4wNDMyNSAxNi4wMjQ4QzYuOTU0MTggMTUuODM0IDYuOTQzMDUgMTUuNjEyOSA3LjAxNjIxIDE1LjQxNDFMOC4wMDg2OSAxMi42NjU3QzguMDg4MjIgMTIuNDU4OSA4LjE1MDI1IDEyLjI0NTggOC4xOTQ3OCAxMi4wMjk1QzguMjM0NTUgMTEuODEgOC4yNjMxNyAxMS41ODczIDguMjgwNjcgMTEuMzY0NkM4LjMxODg0IDEwLjk2MjIgOC4zNDU4OCAxMC41MjY0IDguMzY2NTYgMTAuMTA4MUM4LjM4NzIzIDkuNjg5ODEgOC40MDE1NSA5LjI4NDIzIDguNDEyNjggOC45NDg2M0M4LjQyNyA4LjUzMDMzIDguMzE0MDcgOC41MDMyOSA3Ljk3ODQ3IDguNDIzNzdMNy45MDg0OSA4LjQwNzg2TDUuMDQ1NTcgNy44Njg2OEM0LjgzNzIxIDcuODMyMSA0LjY1MjcxIDcuNzE0NCA0LjUzMTg0IDcuNTQxMDNDNC4yODM3MiA3LjE3ODQgNC4zNzU5NyA2LjY4Mzc1IDQuNzM4NiA2LjQzNTYzQzQuOTEzNTYgNi4zMTYzNCA1LjEyODI4IDYuMjcwMjEgNS4zMzUwNCA2LjMwOTk4TDguNDExMDkgNi44ODczM0M4LjUzMzU2IDYuODk4NDcgOC42NTI4NSA2LjkxMjc4IDguNzc4NSA2LjkyNzA5QzkuMTU3MDQgNi45Nzk1OCA5LjUzODc2IDcuMDA2NjIgOS45MjA0OSA3LjAxMTM5QzEwLjM5NiA3LjAwMTg1IDEwLjg3IDYuOTY2ODYgMTEuMzQyNCA2LjkwNDgzQzExLjQ4NTUgNi44ODg5MiAxMS42MjA3IDYuODcxNDMgMTEuNzU1OSA2Ljg1ODdMMTQuNjU4NiA2LjMxNDc1QzE0Ljg2MzggNi4yNzE4IDE1LjA3ODUgNi4zMTMxNiAxNS4yNTUxIDYuNDI3NjdDMTUuNjE5MyA2LjY3NDIgMTUuNzE0NyA3LjE2ODg1IDE1LjQ2ODIgNy41MzE0OUMxNS40NjY2IDcuNTM0NjcgMTUuNDYzNCA3LjUzNzg1IDE1LjQ2MTggNy41NDEwM0MxNS4zNDI1IDcuNzE1OTkgMTUuMTU5NiA3LjgzNTI4IDE0Ljk1MTMgNy44NzM0NUwxMi4xNzc0IDguMzk1MTRDMTIuMDg1MiA4LjQxNTgxIDEyLjAwMjUgOC40MzAxMyAxMS45MjkzIDguNDQxMjZDMTEuNjM5OCA4LjQ5MDU3IDExLjQ5NjcgOC41MTYwMiAxMS41MTQyIDguOTI3OTZDMTEuNTI2OSA5LjIyODU2IDExLjU2MzUgOS41ODgwMiAxMS42MTEyIDkuOTYzMzhDMTEuNjY2OSAxMC40MDQgMTEuNzQgMTAuODcxNiAxMS44MTY0IDExLjI5OTRDMTEuODY1NyAxMS41ODA5IDExLjkxMTggMTEuODA2OCAxMS45NzU0IDEyLjAyMzFDMTIuMDM5IDEyLjIzOTQgMTIuMTAxMSAxMi40NjA1IDEyLjE5NjUgMTIuNzI2MUwxMy4xNjgzIDE1LjQxNDFDMTMuMzE5NCAxNS44MjYgMTMuMTA2MyAxNi4yODI1IDEyLjY5NDMgMTYuNDMzNkMxMi40OTU1IDE2LjUwNjcgMTIuMjc2IDE2LjQ5NTYgMTIuMDgzNiAxNi40MDY1QzExLjg5MTEgMTYuMzE3NSAxMS43NDMyIDE2LjE1NTIgMTEuNjczMiAxNS45NTY0TDEwLjI0NSAxMi4wMzFMMTAuMDg1OSAxMS43NEw5LjkyNjg1IDEyLjAyMzFIOS45MzQ4Wk05Ljk5NjgzIDMuNTEwNjhDMTAuNzczIDMuNTEwNjggMTEuNDAxMyA0LjEzODkzIDExLjQwMjggNC45MTM1MUMxMS40MDI4IDUuNjg5NjggMTAuNzc0NiA2LjMxNzkzIDEwIDYuMzE5NTJDOS4yMjM4NCA2LjMxOTUyIDguNTk1NTkgNS42OTEyNyA4LjU5NCA0LjkxNjY5QzguNTk0IDQuNTQ0NTEgOC43NDE5MiA0LjE4NjY0IDkuMDA0MzUgMy45MjI2MkM5LjI2Njc5IDMuNjU4NTkgOS42MjQ2NSAzLjUxMDY4IDkuOTk2ODMgMy41MTA2OFpNMTUuNzc4MyA0LjIxNTI3QzEyLjU5MSAxLjAxNjc2IDcuNDEyMjUgMS4wMDcyMSA0LjIxMjE0IDQuMTk2MTlDMS4wMTIwMyA3LjM4NTE2IDEuMDA0MDggMTIuNTYyMyA0LjE5MzA2IDE1Ljc2MjRDNy4zODIwMyAxOC45NjI1IDEyLjU1OTEgMTguOTcwNCAxNS43NTkzIDE1Ljc4MTVDMTcuMjk3MyAxNC4yNDgyIDE4LjE2MjUgMTIuMTY3OCAxOC4xNjQxIDkuOTk2NzhDMTguMTY4OSA3LjgyODkxIDE3LjMxMTYgNS43NDg1MyAxNS43NzgzIDQuMjE1MjdaIiBmaWxsPSIjMDA2QjlCIiAvPgogICAgICAgICAgICA8L2c+CiAgICAgICAgICAgIDxjaXJjbGUgY3g9IjEwIiBjeT0iMTAiIHI9IjkuMjUiIHN0cm9rZT0iIzAwNkI5QiIgc3Ryb2tlLXdpZHRoPSIxLjUiPjwvY2lyY2xlPgogICAgICAgICAgICA8ZGVmcz4KICAgICAgICAgICAgICAgIDxjbGlwcGF0aCBpZD0iY2xpcDBfMjE4XzkyOCI+CiAgICAgICAgICAgICAgICAgICAgPHJlY3Qgd2lkdGg9IjE5LjU1MDYiIGhlaWdodD0iMTkuNTUwNiIgZmlsbD0ibm9uZSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMC4yMjQ3MzEgMC4yMjQ3MikiIC8+CiAgICAgICAgICAgICAgICA8L2NsaXBwYXRoPgogICAgICAgICAgICA8L2RlZnM+CiAgICAgICAgPC9zdmc+)
    :::

-   A tutorial for programming RPC in C++ follows: [[rpc
    tutorial](/d2l/common/dialogs/quickLink/quickLink.d2l?ou=10238929&type=coursefile&fileId=rpc_tutorial.html){rel="noopener"
    target="_blank"}[]{.panorama-alternative-formats-button-container
    title="Alternative Formats for rpc_tutorial.html"
    style="width: 20px !important; height: 20px !important; margin-left: 5px;"}]{.pano-wrapper-div
    style="line-height: 1.9;" accessibility_injected="true"}

    ::: {.panorama-alternative-formats-button tabindex="0" role="button" panorama-document-type="file" style="width: 20px; height: 20px;" aria-label="Alternative Formats for rpc_tutorial.html"}
    ![](data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMjAiIGhlaWdodD0iMjAiIGFyaWEtbGFiZWw9IkFjY2Vzc2liaWxpdHkgU2NvcmUgSWNvbiIgdmlld2JveD0iMCAwIDIwIDIwIiBmaWxsPSJub25lIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPgogICAgICAgICAgICA8Y2lyY2xlIGN4PSI5LjU5MDU2IiBjeT0iOS44MTUzMiIgcj0iOC42NDcyNiIgZmlsbD0id2hpdGUiPjwvY2lyY2xlPgogICAgICAgICAgICA8ZyBjbGlwLXBhdGg9InVybCgjY2xpcDBfMjE4XzkyOCkiPgogICAgICAgICAgICAgICAgPHBhdGggZD0iTTkuOTk2ODMgMC4yMjQ2ODJDMTUuMzk1IDAuMjIzMDkxIDE5Ljc3MzcgNC41OTg1OSAxOS43NzUzIDkuOTk2NzhDMTkuNzc2OSAxNS4zOTUgMTUuNDAxNCAxOS43NzM3IDEwLjAwMzIgMTkuNzc1MkM0LjYwMzQxIDE5Ljc3NjggMC4yMjYzMjIgMTUuNDAxMyAwLjIyNDczMSAxMC4wMDMxQzAuMjI0NzMxIDcuNDA5MDIgMS4yNTM3OSA0LjkyMTQ2IDMuMDg3NjUgMy4wODc2QzQuOTE4MzMgMS4yNTIxNSA3LjQwNDMgMC4yMjE1MDEgOS45OTY4MyAwLjIyNDY4MlpNOS45MzQ4IDEyLjAyMzFMOC41MTEyOSAxNS45NTY0QzguNDQxMzEgMTYuMTU1MiA4LjI5MzM5IDE2LjMxNzUgOC4xMDA5NCAxNi40MDY1QzcuNzAzMzEgMTYuNTkyNiA3LjIyOTM0IDE2LjQyMjQgNy4wNDMyNSAxNi4wMjQ4QzYuOTU0MTggMTUuODM0IDYuOTQzMDUgMTUuNjEyOSA3LjAxNjIxIDE1LjQxNDFMOC4wMDg2OSAxMi42NjU3QzguMDg4MjIgMTIuNDU4OSA4LjE1MDI1IDEyLjI0NTggOC4xOTQ3OCAxMi4wMjk1QzguMjM0NTUgMTEuODEgOC4yNjMxNyAxMS41ODczIDguMjgwNjcgMTEuMzY0NkM4LjMxODg0IDEwLjk2MjIgOC4zNDU4OCAxMC41MjY0IDguMzY2NTYgMTAuMTA4MUM4LjM4NzIzIDkuNjg5ODEgOC40MDE1NSA5LjI4NDIzIDguNDEyNjggOC45NDg2M0M4LjQyNyA4LjUzMDMzIDguMzE0MDcgOC41MDMyOSA3Ljk3ODQ3IDguNDIzNzdMNy45MDg0OSA4LjQwNzg2TDUuMDQ1NTcgNy44Njg2OEM0LjgzNzIxIDcuODMyMSA0LjY1MjcxIDcuNzE0NCA0LjUzMTg0IDcuNTQxMDNDNC4yODM3MiA3LjE3ODQgNC4zNzU5NyA2LjY4Mzc1IDQuNzM4NiA2LjQzNTYzQzQuOTEzNTYgNi4zMTYzNCA1LjEyODI4IDYuMjcwMjEgNS4zMzUwNCA2LjMwOTk4TDguNDExMDkgNi44ODczM0M4LjUzMzU2IDYuODk4NDcgOC42NTI4NSA2LjkxMjc4IDguNzc4NSA2LjkyNzA5QzkuMTU3MDQgNi45Nzk1OCA5LjUzODc2IDcuMDA2NjIgOS45MjA0OSA3LjAxMTM5QzEwLjM5NiA3LjAwMTg1IDEwLjg3IDYuOTY2ODYgMTEuMzQyNCA2LjkwNDgzQzExLjQ4NTUgNi44ODg5MiAxMS42MjA3IDYuODcxNDMgMTEuNzU1OSA2Ljg1ODdMMTQuNjU4NiA2LjMxNDc1QzE0Ljg2MzggNi4yNzE4IDE1LjA3ODUgNi4zMTMxNiAxNS4yNTUxIDYuNDI3NjdDMTUuNjE5MyA2LjY3NDIgMTUuNzE0NyA3LjE2ODg1IDE1LjQ2ODIgNy41MzE0OUMxNS40NjY2IDcuNTM0NjcgMTUuNDYzNCA3LjUzNzg1IDE1LjQ2MTggNy41NDEwM0MxNS4zNDI1IDcuNzE1OTkgMTUuMTU5NiA3LjgzNTI4IDE0Ljk1MTMgNy44NzM0NUwxMi4xNzc0IDguMzk1MTRDMTIuMDg1MiA4LjQxNTgxIDEyLjAwMjUgOC40MzAxMyAxMS45MjkzIDguNDQxMjZDMTEuNjM5OCA4LjQ5MDU3IDExLjQ5NjcgOC41MTYwMiAxMS41MTQyIDguOTI3OTZDMTEuNTI2OSA5LjIyODU2IDExLjU2MzUgOS41ODgwMiAxMS42MTEyIDkuOTYzMzhDMTEuNjY2OSAxMC40MDQgMTEuNzQgMTAuODcxNiAxMS44MTY0IDExLjI5OTRDMTEuODY1NyAxMS41ODA5IDExLjkxMTggMTEuODA2OCAxMS45NzU0IDEyLjAyMzFDMTIuMDM5IDEyLjIzOTQgMTIuMTAxMSAxMi40NjA1IDEyLjE5NjUgMTIuNzI2MUwxMy4xNjgzIDE1LjQxNDFDMTMuMzE5NCAxNS44MjYgMTMuMTA2MyAxNi4yODI1IDEyLjY5NDMgMTYuNDMzNkMxMi40OTU1IDE2LjUwNjcgMTIuMjc2IDE2LjQ5NTYgMTIuMDgzNiAxNi40MDY1QzExLjg5MTEgMTYuMzE3NSAxMS43NDMyIDE2LjE1NTIgMTEuNjczMiAxNS45NTY0TDEwLjI0NSAxMi4wMzFMMTAuMDg1OSAxMS43NEw5LjkyNjg1IDEyLjAyMzFIOS45MzQ4Wk05Ljk5NjgzIDMuNTEwNjhDMTAuNzczIDMuNTEwNjggMTEuNDAxMyA0LjEzODkzIDExLjQwMjggNC45MTM1MUMxMS40MDI4IDUuNjg5NjggMTAuNzc0NiA2LjMxNzkzIDEwIDYuMzE5NTJDOS4yMjM4NCA2LjMxOTUyIDguNTk1NTkgNS42OTEyNyA4LjU5NCA0LjkxNjY5QzguNTk0IDQuNTQ0NTEgOC43NDE5MiA0LjE4NjY0IDkuMDA0MzUgMy45MjI2MkM5LjI2Njc5IDMuNjU4NTkgOS42MjQ2NSAzLjUxMDY4IDkuOTk2ODMgMy41MTA2OFpNMTUuNzc4MyA0LjIxNTI3QzEyLjU5MSAxLjAxNjc2IDcuNDEyMjUgMS4wMDcyMSA0LjIxMjE0IDQuMTk2MTlDMS4wMTIwMyA3LjM4NTE2IDEuMDA0MDggMTIuNTYyMyA0LjE5MzA2IDE1Ljc2MjRDNy4zODIwMyAxOC45NjI1IDEyLjU1OTEgMTguOTcwNCAxNS43NTkzIDE1Ljc4MTVDMTcuMjk3MyAxNC4yNDgyIDE4LjE2MjUgMTIuMTY3OCAxOC4xNjQxIDkuOTk2NzhDMTguMTY4OSA3LjgyODkxIDE3LjMxMTYgNS43NDg1MyAxNS43NzgzIDQuMjE1MjdaIiBmaWxsPSIjMDA2QjlCIiAvPgogICAgICAgICAgICA8L2c+CiAgICAgICAgICAgIDxjaXJjbGUgY3g9IjEwIiBjeT0iMTAiIHI9IjkuMjUiIHN0cm9rZT0iIzAwNkI5QiIgc3Ryb2tlLXdpZHRoPSIxLjUiPjwvY2lyY2xlPgogICAgICAgICAgICA8ZGVmcz4KICAgICAgICAgICAgICAgIDxjbGlwcGF0aCBpZD0iY2xpcDBfMjE4XzkyOCI+CiAgICAgICAgICAgICAgICAgICAgPHJlY3Qgd2lkdGg9IjE5LjU1MDYiIGhlaWdodD0iMTkuNTUwNiIgZmlsbD0ibm9uZSIgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMC4yMjQ3MzEgMC4yMjQ3MikiIC8+CiAgICAgICAgICAgICAgICA8L2NsaXBwYXRoPgogICAgICAgICAgICA8L2RlZnM+CiAgICAgICAgPC9zdmc+)
    :::

## Requirements

-   Implement all services in **C/C++**.
-   Use **SQLite3** for persistent account storage.
-   The **client** reads commands from standard input.
-   Include a **Makefile** with the following targets:
    -   `all`: builds client, virtual bank, BANK1, and BANK2.

    -   `clean`: delete all generated file

    -   `test`: initializes databases, runs services, and performs test
        operations:\

            credit A12345 100
            credit B12345 100
            transfer A12345 B12345 25
            transfer B12345 A12345 10
            transfer B12345 A12345 120
                                

        After tests, print contents of BANK1 and BANK2 databases using
        SQLite3 CLI.

## Timeline

-   **Estimated Effort**: 6--8 hours

## Rubric

  ---------------------------------------- --------
  Criteria                                 Points
  Correct implementation of RPC services   30
  Middleware logic and account mapping     20
  SQLite3 integration and persistence      20
  Makefile and test automation             15
  Code quality and documentation           10
  Proper client interaction                5
  Total                                    100
  ---------------------------------------- --------

## Submission Procedure

Submit a single compressed archive (`zip`, `7z`, or `tar.gz`) named:

    yourMoodleId_a2.zip

Upload it to the iLearn dropbox associated with this assignment.  When
the professor decompresses your submission on on his computer, it should
create a directory call yourMoodleId_a2 with all of you source code in
it.  Your source code will include the Makefile.
