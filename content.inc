% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[LigAnalyst: Interactive Exploration of Ligand Paths through Protein Structures]%
      {LigAnalyst: Interactive Exploration of Ligand Paths through Protein Structures}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author[K. Furmanov\'{a} et al.]
       {Katar\'{i}na Furmanov\'{a}$^{1}$, Miroslava Jare\v{s}ov\'{a}$^{1}$, Jan By\v{s}ka$^{1}$, Adam Jur\v{c}\'{i}k$^{1}$, Julius Parulek$^{2}$, 
        and Barbora Kozl\'{i}kov\'{a}$^{1}$
%        S. Spencer$^2$\thanks{Chairman Siggraph Publications Board}
        \\
% For Computer Graphics Forum: Please use the abbreviation of your first name.
         $^1$Faculty of Informatics, Masaryk University, Czech Republic\\
         $^2$Department of Informatics, University of Bergen, Norway
%        $^2$ Another Department to illustrate the use in papers from authors
%             with different affiliations
       }

% ------------------------------------------------------------------------

% if the Editors-in-Chief have given you the data, you may uncomment
% the following five lines and insert it here
%
% \volume{27}   % the volume in which the issue will be published;
% \issue{1}     % the issue number of the publication
% \pStartPage{1}      % set starting page


%-------------------------------------------------------------------------
\begin{document}

% \teaser{
%  \includegraphics[width=\linewidth]{eg_new}
%  \centering
%   \caption{New EG Logo}
% \label{fig:teaser}
% }

\maketitle

\begin{abstract}
Protein structures and their interaction with ligands has been in the scope of biochemistry and structural biology research for decades.
In the most complex situation the ligand has to follow a path (tunnel) from the outer solvent to the active site where it can react.
This transportation can be very lengthy and complex process which is influenced by both geometric and physico-chemical properties of the ligand and the amino acids surrounding the tunnel.
When studying this process in molecular dynamics simulations, proper understanding of ligand behavior inside the tunnel is crucial.
For this purpose we proposed a novel method for the interactive exploration of ligand transportation to the active site.
As the path of the ligand is usually very jittered and full of impasses, we come with the path simplification model which stresses the main direction of movement of the ligand.
In our representation we introduce a concept of so called temporal tunnel and show its main properties and its surrounding amino acids.
By interacting with this representation of the user can explore the overall appearance of the temporal tunnel as well as selected interesting portions of the original ligand movement.
These interesting time sequences are revealed by interacting with our representation.
This approach helps select only the time sequences containing the interesting ligand movements. 
It dramatically decreases the length of the molecular dynamics simulation which is worthwile to scrutinize as well as the time spent on this exploration.
The proposed method was tested on the simulations captured by the biochemists who also evaluated the method.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}



%-------------------------------------------------------------------------
\section{Introduction}
Studying possible reactions between different types of molecules forms an interesting research problem already for decades.
Proper understanding of all processes occurring when two or more molecules react helps in the design of new chemical matters, e.g., in drug design or protein engineering.
Namely in these fields the researchers are aiming to combine a protein with a given ligand in order to design new drug or to change the protein properties and function.
In this particular case the ligand has to be transported from the outer solvent to the protein active site where the chemical reaction between the ligand and the amino acids surrounding the active site can undergo.
The consecutive reaction then changes the constitution and properties of both molecules. 
In protein engineering, for example, the goal is to change the protein properties so the new protein is, e.g., more stable and resistant to organic cosolvents \cite{Koudelakova2013}.

The complexity of the design of such described reaction lies namely in the transportation of the ligand to the protein active site.
As the active site is usually buried deeply in the protein structure and thus inaccessible directly from its surface, the ligand has to find a suitable transportation path through the protein structure.
This process, called molecular docking, is very complex, lengthy, and costly. 
Therefore, researchers are searching for solutions how to simplify and ease the search for proper ligand binding.
Currently available solutions are often focusing on the detection of possible ligand transportation paths through the protein, called tunnels.
They are mostly based on the geometric analysis and detection of such tunnels (e.g., CAVER \cite{Chovancova2012}, MOLE \cite{Sehnal2013}, or MolAxis \cite{Yaffe2008}).
Other approaches, such as MoMA-LigPath \cite{Devaurs}, are aiming to simulate the ligand transportation itself.
Simulating the ligand docking using current computational approaches is still a challenging problem.
There are several available variants of molecular simulation methods devised specifically to this problem. 
Among them belong the Steered Molecular Dynamics \cite{Isralewitz} and Random Acceleration Molecular Dynamics \cite{Ludemann} which are able to simulate the ligand binding. 
Such simulations produce large amount of data containing the ligand movements which have to be subsequently explored by the domain expert.
As the length of these simulation currently can reach to hundreds of thousands of time steps and this amount is increasing thanks to the available computational resources, it becomes impossible for the domain expert to observe the ligand movement step by step.
But the simulation length is not the only problem. 
Simulations often contain movements which are irrelevant with respect to the ligand binding.
For example, a significant portion of the simulation the ligand usually spends outside the protein searching for a proper tunnel gorge to enter the molecule. 
Often it also happens that the ligand enters the molecule using a wrong tunnel and is evicted from the molecule and searches for the entrance repeatedly.
So the real ligand entering to the active site can be in fact captured in a smaller subset of the original sequence.

These problems are addressed by our novel approach for visual analysis of ligand transportation to the active site which we introduce in this paper.
Our aim is to provide the domain experts with a tool for intuitive and interactive exploration of already captured molecular dynamics simulation containing the process of ligand binding. 
Using our proposed method the users are able to filter out parts of the simulation which do not lead the ligand to the active site.
In the filtered data we provide the users with our newly introduced concept of so called temporal tunnel which shows the ligand transportation to the active site on different levels of detail.
In the most abstracted view the temporal tunnel shows only the significant shifts of the ligand towards the active site and the user can interactively explore selected time portions in more and more detail.
This abstracted representation is interactively linked with the 3D visualization window where the exact shape of the temporal tunnel on a given level is visualized.
Except for the temporal tunnel itself, our tool enables to explore the amino acids surrounding the ligand along its path to the active site as well.

Our proposed solution was thoroughly tested and evaluated by the domain experts from protein engineering.
They performed the evaluation on their own simulations and their feedback is mentioned in Section \ref{discussion}.

%-------------------------------------------------------------------------

\section{Related Work}
\cite{bidmon2008}, \cite{lampe2011}, \cite{turkay2011}

%-------------------------------------------------------------------------
\section{Problem Description and Input Data}

%-------------------------------------------------------------------------
\section{LigAnalyst Design and Implementation}

%-------------------------------------------------------------------------
\section{Results}
The results will be demonstrated on one or two case studies.

%-------------------------------------------------------------------------
\section{Discussion} \label{discussion}
Here will be the summary of feedback from biochemists.

%-------------------------------------------------------------------------
\section{Conclusion and Future Work}


%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{refs}

\end{document}
