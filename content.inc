% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels]%
      {Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels}

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
Protein structures and their interaction with ligands have been in the focus of biochemistry and structural biology research for decades.
%Traditionally the interaction is represented by a ligand that follows a path (tunnel) from the outer solvent to the active site where it can react.
%The transportation of ligand into the protein active site where it can react can be very lengthy and complex process that is influenced and driven by both geometric and physico-chemical properties of the ligand and the amino acids surrounding its path.
The transportation of ligand into the protein active site is often complex process, driven by geometric and physico-chemical properties, which renders the ligand path full of jitter and impasses. Therefore, answering also the domain expert needs, we design an explorative visualization solution based on a multi-scale simplification model. This allows to emphasize the main direction of the ligand motion while providing geometric and physico-chemical descriptors available at each hierarchical level by user interaction.  
%These interesting time sequences are revealed by interacting with our representation.
This approach could easily guide users to choose simulation frames containing important ligand movements that drive the ligand to the active site. 
Additionally, our simplified representation decreases the length of molecular dynamics simulation, which significantly reduces the time spent on this analysis.
The proposed method was applied on simulations captured by the biochemists who also evaluated the method.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}



%-------------------------------------------------------------------------
\section{Introduction}
Studying possible reactions between different types of molecules forms an important research problem already for decades.
Proper understanding of all processes occurring when two or more molecules react helps in the design of new chemical matters, e.g., in drug design or protein engineering.
Namely in these fields the researchers are aiming to combine a protein with a given ligand in order to design new drug or to change the protein properties and function.
In this particular case the ligand has to be transported from the outer solvent to the protein active site where the chemical reaction between the ligand and the amino acids surrounding the active site can undergo.
The consecutive reaction then changes the constitution and properties of both molecules. 
In protein engineering, for example, the goal is to change the protein properties so the new protein is, e.g., more stable and resistant to organic cosolvents~\cite{Koudelakova2013}.

The complexity of the design of such described reaction lies namely in the transportation of the ligand to the protein active site.
As the active site is usually buried deeply in the protein structure and thus inaccessible directly from its surface, the ligand has to find a suitable transportation path through the protein structure.
This process, called molecular docking, is very complex, lengthy, and costly. 
Therefore, researchers are searching for solutions how to simplify and ease the search for proper ligand binding.
Currently available solutions are often focusing on the detection of possible ligand transportation paths through the protein, called tunnels.
They are mostly based on the geometric analysis and detection of such tunnels (e.g., CAVER~\cite{Chovancova2012}, MOLE~\cite{Sehnal2013}, or MolAxis~\cite{Yaffe2008}).
Other approaches, such as MoMA-LigPath~\cite{Devaurs}, are aiming to simulate the ligand transportation itself.
Simulating the ligand docking using current computational approaches is still a challenging problem.
There are several available variants of molecular simulation methods devised specifically to this problem. 
Among them belong the Steered Molecular Dynamics~\cite{Isralewitz} and Random Acceleration Molecular Dynamics~\cite{Ludemann} which are able to simulate the ligand binding. 
Such simulations produce large amount of data containing the ligand movements which have to be subsequently explored by the domain expert.
As the length of these simulation currently can reach to hundreds of thousands of time steps and this amount is increasing thanks to the available computational resources, it becomes impossible for the domain expert to observe the ligand movement step by step.
But the simulation length is not the only problem. 
Simulations often contain movements which are irrelevant with respect to the ligand binding.
For example, a significant portion of the simulation the ligand usually spends outside the protein searching for a proper tunnel gorge to enter the molecule. 
Often it also happens that the ligand enters the molecule using a wrong tunnel and is evicted from the molecule and searches for the entrance repeatedly.
So the real ligand entering to the active site can be in fact captured in a smaller subset of the original sequence.

These problems are addressed by our novel approach for visual analysis of ligand transportation to the active site which we introduce in this paper.
Our aim is to provide the domain experts with a tool for intuitive and interactive exploration of already captured molecular dynamics simulation containing the process of ligand binding. 
Using our proposed method the users are able to distinguish between the parts of the simulation when the ligand searches for the proper path to the active site (searches the tunnel gorge or enters the wrong tunnel) and the part when the ligand finally leads to and reaches the active site.
In the part of such annotated data when the ligand travels to the active site we provide the users with our newly introduced concept of so called temporal tunnel.
The centerline of this tunnel is represented by the ligand trajectory and in the original data is very jittered.
Thus it is hard to follow determine the time steps when the ligand made a significant shift towards the active site.
To ease this, we come with two methods for simplification of the original trajectory.
These methods can simplify the ligand path on several levels of detail.
In the most abstracted view the temporal tunnel shows only the significant shifts of the ligand towards the active site and the user can interactively explore selected time portions in more and more detail.
This abstracted representation is interactively linked with the 3D visualization window where the exact shape of the temporal tunnel on a given level is visualized.
Except for the temporal tunnel itself, our tool enables to explore the amino acids surrounding the ligand along its path to the active site as well.

Our proposed solution was thoroughly tested and evaluated by the domain experts from protein engineering.
They performed the evaluation on their own simulations and their feedback is mentioned in Section~\ref{discussion}.

%-------------------------------------------------------------------------

\section{Related Work}
Interactive exploration of ligand paths through protein structures is a complex problem that requires elaborate analysis of existing and suitable approaches to its subtasks.
In this section we present the results we consider to be relevant to our proposed solution. 
As our tool consists of several parts, this section will be divided with respect to these parts as well. 
Studying the ligand transport path is tightly related to the analysis of its trajectory.
Thus, the first part will cover the topic related to the trajectory analysis, simplification, and visualization.
Then the existing representations of tunnels and their surrounding amino acids will be mentioned.

\subsection{Trajectory Analysis, Simplification, and Visualization}
When searching for the inspiration in this field, one of the best starting points is the book by Andrienko et al. \cite{andrienko2013}.
Concerning the trajectory simplification, they proposed two different approaches to the data abstraction, which is a necessary step to achieve the reduction of the data and clarity of visualizations.
First approach is characterized by omitting unnecessary positions and segments.
The other is based on sampling the data.
Andrienko et al. also claim that there are no general methods for sampling trajectories.
Thus the suitability of particular sampling method is deduced from what information is considered important.
A recent work of Vrotsou et. al. \cite{Vrotsou2015} introduced a systematic stepwise methodology for trajectory simplification with emphasis on visual analysis.
Even though they primarily developed the tool to analyze three dimensional trajectories (aircraft flights), it is not limited to them.

In the field of molecular biology as well as systems biology, there are several examples of methods focusing on the trajectory analysis.
Bidmon et al.~\cite{bidmon2008} presented an abstract way of identification and visualization of solvent molecules' pathways within a molecular dynamics. 
In comparison to previous solutions, their approach preserves valuable information on the directions and velocities of water molecules routing along these paths. 
Another approach to the guidance through a complex simulation trajectories in systems biology was presented by Luboschik et al.~\cite{Luboschik2012}. 
Their method was proposed for biochemical reaction networks and aims to provide the users with the the tool for investigating the overall behavior of a modeled system and subtle, detail behavior at the same time.

\subsection{Visualization of Tunnels}
Our notion about the temporal tunnel in the protein resembles the approach of Lindow et al. \cite{Lindow2013}.
In this work they focus on the interactive exploration of the dynamics of protein cavities which can form the transportation path for a ligand. 
They are able to calculate and visualize the cavity volume and to analyze the time-dependent changes of the cavity structure.
The cavity dynamics is captured by rendering the cavities in a single image. 
The resulting image is visualized using molecular surface representation colored according to time. 

TODO!!!!!!

%\cite{bidmon2008}, \cite{lampe2011}, \cite{turkay2011}, and this is new 

%-------------------------------------------------------------------------
\section{Problem Description and Input Data}
When studying long molecular dynamics simulations, the researchers have to face namely the following high-level tasks:
\begin{itemize}
\item Detect the part of the simulation where the ligand enters the protein and finally reaches the active site.
\item Explore this route in detail and detect its bottlenecks.
\end{itemize}
In consequence, these steps are performed in order to reveal the parts of the trajectory where the ligand gets stuck.
It means that in such parts there are some obstacles made by the surrounding amino acids.
These obstacles can be geometric (the empty space between these amino acids is too narrow) or physico-chemical (the properties of the amino acids are incompatible with the ligand properties), or their combination.
The geometric obstacles can be detected by using an algorithm for tunnel computation in molecular dynamics (e.g., CAVER~\cite{Chovancova2012} or MOLE~\cite{Sehnal2013}).
These tools are able to produce the information about time evolution of individual tunnels and for each tunnel detect its bottleneck -- the narrowest part limiting the size of the ligand aiming to pass through this tunnel.
Figure~\ref{fig:tunnel} shows an example of small ligand passing through a tunnel computed by CAVER algorithm and visualized using CAVER Analyst~\cite{Kozlikova2014}. 
The tunnel is colored with respect to the hydrophobicity of the surrounding amino acids and the geometric bottleneck of the tunnel is clearly visible.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/tunnel.png}
  \caption{\label{fig:tunnel} Small ligand (green) passing through a tunnel represented by the transparent surface. The surface encloses the available empty space along the tunnel centerline and is colored with respect to the hydrophobicity of the surrounding amino acids (hydrophobic -- red, hydrophylic -- blue, neutral -- violet). The active site is located in the left ending of the tunnel.}
\end{figure}

However, this bottleneck can be to some extent influenced by the passing ligand and this influence is also determined by the physico-chemical properties of the ligand and the bottleneck-lining amino acids (e.g., hydrophobicity or partial charges of individual atoms).
To reveal such dependencies, it requires the involvement and experience of the domain expert who has to study the ligand trajectory captured in the molecular dynamics simulation.
And for such task a proper visual representation and guidance through such large data is substantial.

In protein engineering, all these effort can finally lead to the detection of amino acids along the ligand trajectory which caused problems, i.e., were the key players in situations when the ligand got stuck.
Such amino acids are then the best candidates for subsequent mutation of the protein chain when these amino acids are replaced by more suitable ones wrt. their size and properties.
On the other hand, in drug design the aim is to propose modifications of the ligand to increase its binding and so design a better drug produced from this ligand.

\subsection{Input Data}
As already mentioned, the input data are formed by the simulations of molecular dynamics which contains the movements of the protein and one or more ligands.
Ligands can follow two main routes -- they can be transported from the outside environment to the protein active site or vice versa (after the desired reaction the product leaves the protein).
Our proposed tool is suitable for both cases.

The length of the simulations may vary from few hundreds to hundreds of thousands of time steps.  
This depends namely on the ligand speed and its ability to find the proper path to the active site.
Figure \ref{fig:lig_movement} shows an example of a ligand trajectory consisting of 10.000 time steps. 

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/lig_movement.png}
  \caption{\label{fig:lig_movement} Ligand trajectory for a simulation containing 10.000 time steps. TODO change image, add molecule}
\end{figure}

Long simulations can often contain many time steps when the ligand followed an impasse -- it tried to find the proper entrance point to the protein (tunnel gorge) or entered a wrong tunnel and had to return.
Such parts of the simulation could be of less interest so the user should be provided with a possibility to filter them out and focus only on the interesting parts.

%-------------------------------------------------------------------------
\section{Design and Implementation}
In this section we describe the design rationale of our proposed approach to interactive exploration of ligand trajectory coming from the above described simulations of molecular dynamics.
The design is tightly related to the problems posed by the biochemists, namely:
\begin{itemize}
\item The length of the simulations and impossibility to distinguish between different parts based on the type of ligand movement (outside protein, inside a wrong or correct tunnel).
\item The scattered nature of the original movement making impossible to easily follow the overall direction of the ligand movement.
\end{itemize}

As a solution we come with our novel representation illustrated in Figure~\ref{fig:overview}.
The first problem is addressed by the simple visualization on the top of the window.
Its goal is to provide the users with the general overview of the whole simulation and highlighting individual parts of the ligand movement.
We distinguish between three basic types of ligand movement which are detected in the following way.
In each time step we check the position of the ligand with respect to the protein solvent excluded surface~\cite{Richards}. 
If the ligand is outside the protein surface, it means that it is searching for the entrance point to enter the protein through a tunnel gorge on the surface. 
When the ligand enters the protein inner space, we can distinguish between two cases.
In the first case the ligand enters a tunnel but there is an obstacle preventing it to get to the active site and the ligand is expelled from the inner space back to the outer environment.
The second case finally enables the ligand to reach the active site. 
Very similar solution can be adopted for the opposite direction when the ligand aims to leave the active site and reach the outer solvent.

As a result, we obtain three different types of movements which are highlighted in the overview representation (see Figure \ref{fig:overview} a)).
Yellow parts represent the ligand movements outside the molecule, red parts show the parts when the ligand entered a wrong tunnel and had to return, and green parts depict the situation when the ligand finally took the correct tunnel and reached the active site.
The user can interactively select an arbitrary part and the remaining parts of our proposed solution (see Figure~\ref{fig:overview} b)) are interactively updated in order to present only the information for a selected part.

\begin{figure*}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/overview.png}
  \caption{\label{fig:overview} Illustration of our proposed technique. Section a) gives an overview of the individual parts of the simulation (yellow = ligand is outside the protein, red = ligand entered a wrong tunnel, green = ligand entered a correct tunnel and reached the active site). Section b) shows the detailed information about a selected part. TODO}
\end{figure*}

\subsection{Temporal Tunnel}
The bottom part of our visualization consists of three tightly related sections (detailed description in Section~\ref{visualization}) showing the properties of so called \textit{temporal tunnel}. 
We define the temporal tunnel as a set of spheres positioned onto the centerline representing the trajectory of ligand. 
The centers of these spheres correspond to the center of gravity of the ligand in each its position and the diameter of the spheres is computed as the maximal empty space around the ligand in a given time step. 
The main contribution of the temporal tunnel is to give the user the information about the geometric bottlenecks (narrowest parts) along the ligand trajectory.
However, the temporal tunnel applied to the original data is not meaningful (see Figure \ref{fig:temporal}).
However, when the ligand trajectory is simplified using one of the methods described below, it gives the user an important overview of the bottlenecks which can be subsequently explored in more detail.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/temporal.png}
  \caption{\label{fig:temporal} Left: selected part of the whole trajectory when the ligand enters the active site. Right: visualization of the corresponding temporal tunnel. TODO change images!}
\end{figure}

\subsection{Trajectory Simplification}

\subsection{Trajectory Visualization} \label{visualization}
The trajectory is visualized in two manners which are interactively linked together.
First is the abstracted visualization shown in Figure~\ref{fig:overview} b) where the visualization of the temporal tunnel and its surroundings is divided into three parts. TODO

The second type of visualization shows the trajectory as a tube in 3D. TODO


\subsection{Jan's part, will probably not fit to the current version at all.}
%General outline of the section:
% - detection of the ligand entering tunnel
%   - sphere, problems
%	  - surface, computed using LSMS 
% - results in overview
%	  - enables select the appropriate time range
% - once the range is selected the aggregation is done
%   - why aggregation
%	 - how it is done
%      - two or three methods - all?
%   - bar char + 3D line as the results
% - what can be important with respect why the tunnel get stuck
%   - geometrical properties = radius chart
%	    - how we compute radius
%	 - biochemical properties = AA chart
%		  - how we compute surrounding AA

As mentioned in previous section the very first problem the biochemist face, while exploring the input data, is to detect the part of the simulation where the ligand enters the protein. 
In our approach we suggest to employ the molecular surface as a threshold - i.e., whenever the ligand crosses the borderline of the volume defined by the molecular surface the time in simulation and ligand position is stored as entrance point.
%The precision of entry point detection higly depends on used alorithm for computation of the molecular surface. In our implementation we used LSMS ({\color{red}cite}) with following settings: TODO. LSMS is currently not the best one neither it is actually implemetend (I guess I will stick with sphere for time reasons), so I don't recommend to mention it.

%Just some ramainings:
%The positions of the active site enables to detect the exact time when the ligand was presented there. 
%Using this knowledge, the simulation can be backtracked or followed forward as required. 
%To detect the exact point of entrance we suggest to used molecular surface as a threshold, i.e., whenever the ligand is outside of the volume defined by the molecular surface the time is stored as entrance point.


Since the ligand may reenter the molecule more then once during the whole simulation, we obtain several discrete intervals. 
In order to provide the whole simulation overview we suggest to use simple visualization as shown in Figure \ref{fig:overview}a. 
On such visualization the size of individual intervals (represented as rectangles) and their positions in simulation can be easily spotted. 
From here the biochemist can easily navigate to the proper time span they want to explore in more detail.

Even though the individual intervals are usually much shorter in comparison with the whole simulation it is still nearly impossible to comprehend the whole information. Neither an aggregate information in single image (see Figure \ref{fig:ligand-path-interval}) or watching the whole play-through would work since the amount of data is still too high. 
Hence we suggest the solution based on a multi-scale simplification model where the already mentioned overview creates its higher level.  

We developed the following model in order to emphasis multiple important aspects of the simulation such as: the main direction of the ligand motion, parts of the simulation where the ligand get stuck and geometrical and physico-chemical properties of such places. 
The main source of the clutter (see Figure \ref{fig:temporal} left) in the data is caused by random Brownian motion of the molecule and ligand.
To reduce this jitter the Hermite (or similar) interpolation can be used.
However, such reduction is not enough since the time difference and hence the spacial distance between two time steps is usually very small (few femtoseconds, picosecond at most). 
Therefore, the ligand trajectory will still contains great number of loops even though it is smoother.
{\color{red} Should we define what the loop is? - I mean, I'm using it later quite lot. I did partial defined it in \textbf{Second} but its maybe too late.}


Therefore we propose {\color{red}approach / several different approaches}...

\textbf{First:} ... based on comparison of surrounding amino acids. 
We have already mentioned that the biochemical and geometrical aspects along the ligand path plays an important role during its exploration. 
Note that both these properties are defined by surrounding amino acids. 
Therefore we utilize this information and aggregate all the ligand positions into a single cluster if they have similar surroundings. 
The number of allowed changes in surrounding amino acids directly corresponds to the individual levels in our multi-scale model. 
{\color{red} Note that these levels are limited to three since for each time step we compute only three closes amino acids.}.

At lowest level (when no amino acids can be changed in single cluster) the model aggregate only the smallest loops in the same area. 
While all the loops (longer or smaller) on border between two places with different amino acids and hence different properties are preserved.  
This applies also for higher levels, however, the change there would have to be more significant.

Such model also allows to evaluate how long the ligand was stuck in surroundings of some particular amino acids. 
Which provides useful hints when detecting which amino acids along the ligand trajectory caused problems and should be possibly replaced.

{\color{red} TODO: reason about / and implement the time flow independence}


\textbf{Second:} ... based on number of loops that ligand performs. 
When exploring the ligand path in more details the biochemist are interested mostly in the parts where the ligand get suck for some reason.
We suggest to employ the position of active site which can be either user defined or in some cases obtained directly from the simulation.
{\color{red}(The automatic active site detection is currently supported only for input data in which the ligand is in the active site by the end of the simulation.)}.
% I guess it could be done for reentry simulation as well using the most distant place from entery point. But here we face the problem how to evalueate whether the ligand go stuck and lefet before actually reaching the active site (ever).  
In each time step the distance from such active site to the ligand can be evaluated.
Using this knowledge it is possible to detect places when the ligand movement changes its direction.

The multi-scale model is then build from the the beginning of the evaluated interval and follows the simulation forward in time. 
Individual time steps are aggregated in the way that the ligand has to make a given number of loops (each loop is defined by two direction changes) before new cluster is created.
In other words, each resulting cluster contains the given number of loops (except the last one which is allowed to have less).
{\color{red}TODO I have to think about loops vs. single changes aggregation}

Since there is a constant number of loops before a new cluster is created, it takes more time (time steps) to accumulate such number if the ligand is moving in single direction.
Hence, counting the time steps in each cluster instantly reveals the parts of the simulation where the ligand was moving mostly in a single direction or it was osculating. 
This information, however, has to be combined with the actual distance which the ligand crossed in order to avoid misinterpretation of long loops. 
%This information is visualized using color - or whatever

Even though this multi-scale model enables to switch between individual levels by increasing (or decreasing) the number of loops in cluster by one, we suggest that the current value should be multiplied (or divided) by a natural number. 
This way clusters will be merged or divided uniformly, e.g, if the current number of loops in cluster is multiplied by two the two adjacent cluster will be merge into the single one and vice versa.

\textbf{Third:} ... based on uniform distribution of time.
In this model we uniformly divide the whole simulation into the given number of clusters. 

Such model can help to evaluate how much the ligand was stuck for a given amount of time.

The advantage of this approach is its uniformity which allows easily transfer from one level to another.

%\textbf{Fourth:} ... based on threshold for maximum backtracking of the ligand on its path. This is not good approach since I don't even know how to justify it with respect to previous three.

\subsection{Visualization}

{\color{red} Just some random sentences I come up with but then in the end did not fit in:}

In order to communicate all the information obtained from previous models to the user we proposed a visualization as shown in Figure \ref{fig:overview}.

Each cluster is here represented by a single bar where its height corresponds to the amount at which the ligand was stuck.

Each cluster is represented by the last time step it contains.
This helps to revel the conditions such as tunnel radius which enabled to the ligand proceed further towards the active site.


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
