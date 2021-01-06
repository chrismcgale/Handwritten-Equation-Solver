# Handwritten Equation Solver
*This is the first of hopefully many AI and deep learning projects I hope to complete so stayed tuned*

The purpose of this assignment is to demonstrate how a CNN can distinguish between a large assortment of possible identifiers through the context of math symbols.

There are many parts to this project so please let me know if at any time you notice something I could improve!

How it Works?
First the client draws any of the predefined symbols. The client can then either submit, or clear. If the client submits, the image is processed and sent to the CNN which then predicts which symbol was drawn. The client then has the option to either accept the predicted symbol and move on or to redraw it. At any time the client can submit their equation. This string is sent to scanner to tokenize the symbols and create a parse tree. This tree can then be sent to the equation solver and return the correct output.

Why do we need to usse a parse tree?
Some equations such as (((((+4 may have correct terms but are meaningless and will produce an error, this is an equation solver not an app that sends it's questions to google. The parse tree is to ensure the string follows correct mathematical syntax and tells us exactly where any error occurs. This allows us to expand our syntax and forms the begining of an English text reader.

Why I chose this project? As a math major I know firsthand that when writting equations for long periods of time my hand gets tired and my writting becomes attrocious(Which is why I learnt top write with my left hand too). This has caused me a number of problems with markers being unable to identify some of my work. Hence this project.

Possible uses
    Schools and universities to grade simple responses
    Handwritten notes to text(tablets, picture to text)
    Self driving cars to read street signs

Areas of improvement
    -One can always optimize the layers of a model for a more accurate result
    -Allowed variables and text

Difficulties
    -Large number of files created for train/valid/test
    -The canvas

References
    Incredibly helpful AI and CNN course https://deeplizard.com/
    Data set https://www.kaggle.com/xainano/handwrittenmathsymbols

