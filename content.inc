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
\section{Discussion}
Here will be the summary of feedback from biochemists.

%-------------------------------------------------------------------------
\section{Conclusion and Future Work}


%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{refs}

\end{document}
