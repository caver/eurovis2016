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
Abstract here   

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}



%-------------------------------------------------------------------------
\section{Introduction}

%-------------------------------------------------------------------------
\section{Related Work}
The interactive exploration of ligand paths through protein structures is a complex problem that requires elaborate analysis of existing and suitable approaches to its subtasks.
Namely, it can be divided into trajectory analysis, simplification and visualization, temporal representation of tunnels, and visualization of protein residues' properties along the ligand path.


Bidmon et al. \cite{bidmon2008} presented an abstract way of identification and visualization of solvent molecules' pathways within a molecular dynamics. 
In comparison to the previous solutions, their approach preserves valuable information on the directions and velocities of water molecules routing along these paths. 


%\cite{bidmon2008}, \cite{lampe2011}, \cite{turkay2011}, and this is new \cite{andrienko2013}

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
