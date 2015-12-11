% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title[Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels]%
      {Interactive Exploration of Ligand Movements through Multiscale Temporal Tunnels}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author[Furmanov\'{a} et al.]
       {K. Furmanov\'{a}$^{1}$, M. Jare\v{s}ov\'{a}$^{1}$, J. By\v{s}ka$^{1,2}$, A. Jur\v{c}\'{i}k$^{1}$, J. Parulek$^{2}$, H. Hauser$^{2}$, and B. Kozl\'{i}kov\'{a}$^{1}$
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

 %\teaser{
 % \includegraphics[width=\linewidth]{img/teaser}
 % \centering
 %  \caption{Illustration of our proposed solution for interactive exploration of ligand movements. The information whether the ligand is outside or inside the molecular surface is depicted as a two color line (0). The bar chart showcases the most prominent motion patterns inside each detected temporal block (1). Correspondingly, we form a simplified representation of the ligand trajectory that has the same number of control points as is the number of temporal blocks (2). Each temporal block is described by several features that include the radius of the sphere enclosed void around the ligand (3a) and physico-chemical properties of amino acids interacting with the ligand (3b).}
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
The study of reaction processes between different types of molecules has been an important research problem already for decades.
A proper understanding of the processes occurring when two or more molecules react helps in the design of new chemical matters, e.g., in drug design or protein engineering.
Here, the researchers aim to combine a protein with a given ligand in order to design a new drug or to change protein properties and their function.
In these particular cases the ligand has to be transported from the outer solvent to the protein active site where the chemical reaction between the ligand and the amino acids surrounding the active site takes place.
The consecutive reaction then changes the composition and properties of both molecules. 
In protein engineering, for example, the goal is to alter the protein properties so that the new protein is, e.g., more stable and resistant to organic cosolvents~\cite{Koudelakova2013}.


\begin{figure*}
  \includegraphics[width=\linewidth]{img/teaser}
  \caption{\label{fig:teaser}Illustration of our proposed solution for interactive exploration of ligand movements. The information whether the ligand is outside or inside the molecular surface is depicted as a two color line (0). The bar chart showcases the most prominent motion patterns inside each detected temporal block (1). Correspondingly, we form a simplified representation of the ligand trajectory that has the same number of control points as is the number of temporal blocks (2). Each temporal block is described by several features that include the radius of the sphere enclosed void around the ligand (3a) and physico-chemical properties of amino acids interacting with the ligand (3b).}
\end{figure*}


The design complexity of such reactions lies namely in the transportation of the ligand to the protein active site.
As the active site is usually buried deeply in the protein structure and thus inaccessible directly from its surface, the ligand has to find a suitable transportation path through the protein structure.
This process, called molecular docking, is very complex, lengthy, and its analysis is heavy on computational resources. 
Therefore, researchers aim at solutions that simplify and ease the analysis for proper ligand binding.
Currently available solutions often focus on detection of possible ligand transportation paths through the protein, called tunnels.
These solutions are mostly based on the geometric analysis, which lead to the tunnel detection in the end, e.g., CAVER~\cite{Chovancova2012}, MOLE~\cite{Sehnal2013}, or MolAxis~\cite{Yaffe2008}.
Other approaches, such as MoMA-LigPath~\cite{Devaurs}, aim at simulating the ligand transportation itself.
Nevertheless, simulating the ligand docking using current computational approaches is still a challenging problem.
There are several available variants of molecular simulation methods devised specifically to this problem. 
Among these Steered Molecular Dynamics~\cite{Isralewitz} and Random Acceleration Molecular Dynamics~\cite{Ludemann} are able to simulate the ligand binding. 
Such simulations produce a large amount of data containing the ligand movements that are to be explored by the domain expert.
As the length of these simulations reaches often hundreds of thousands of time steps, it becomes impossible for the domain experts to visualize and observe the ligand movement in a frame-by-frame manner.
Moreover, the simulation often contains movements that are irrelevant to the ligand binding.
For example, a significant portion of the simulation the ligand usually spends outside the protein searching for a proper tunnel gorge to enter the molecule. 
It also often happens that the ligand enters the molecule via a wrong tunnel and is then evicted from the molecule and searches for the entrance repeatedly.
Therefore, the "true" active site entering can be in fact captured in a smaller subset of the original sequence.




In this paper, we propose a new visual analysis system that addresses the aforementioned challenges, i.e.,  the transportation of a ligand to the active site. 
We aim to provide the domain experts with a tool for intuitive and interactive exploration of already captured molecular dynamics simulation containing the process of ligand binding. 
Using our proposed solution the users are able to distinguish between the parts of the simulation where the ligand searches for the proper path to the active site (searches the tunnel gorge or enters the wrong tunnel) and the part where the ligand finally leads to and reaches the active site.
%In the part of such annotated data when the ligand travels to the active site we provide the users with our newly introduced concept of so called temporal tunnel.
%The centerline of this tunnel is represented by the ligand trajectory and in the original data is very jittered.
%Thus it is hard to follow determine the time steps when the ligand made a significant shift towards the active site.

Here, we introduce four dedicated methods for simplification of the original trajectory.
These methods can simplify the ligand path hierarchically, thus providing several levels of detail (LOD), which can be interactively examined.
In the most abstracted view, represented as the top-most LOD, the temporal tunnel shows only the significant shifts of the ligand towards the active site. 
Here, the user can interactively brush time intervals, which automatically reveals and adopts the temporal tunnel to the selected interval.
This abstracted representation, providing the brushing capabilities, is interactively linked with the 3D visualization where the 3D shape of the temporal tunnel for the given temporal window is displayed.
Further, our tool enables to explore the amino acids surrounding the ligand along its path to the active site as well.

Our proposed solution was thoroughly tested and evaluated by the domain experts from protein engineering.
They performed the evaluation on their own simulations and their feedback is described in Section~\ref{discussion}.

%-------------------------------------------------------------------------

\section{Related Work}
The interactive exploration of ligand paths through protein structures is a complex problem that requires an elaborate analysis of existing and convenient approaches.
%In this section we present the results we consider to be relevant to our proposed solution. 
As our system addresses several areas, this section will be divided with respect to these areas as well. 
Studying the ligand transport path is tightly related to the analysis of its trajectory.
Thus, the first part will cover the topic related to the trajectory analysis, simplification, and visualization.
Then the existing representations of tunnels and their surrounding amino acids will be addressed.

\subsection{Trajectory Analysis, Simplification, and Visualization}
When searching for the most appropriate trajectory simplification method, the taxonomy of different movement patterns introduced by Dodge et al.~\cite{Dodge2008} can help to categorize the type of motion and to propose an appropriate solution for the analysis and simplification.
Then, Andrienko et al.~\cite{andrienko2013} describe a legacy of tools and approaches to analyze trajectory data.
With respect to the trajectory simplification, they introduce two approaches to data abstraction representing a necessary step to achieve the reduction of the data in order to achieve informative visualizations.
The first approach is characterized by omitting unnecessary positions and segments, while the second exploits data subsampling.
On the other hand, they state that there is no general method to sample trajectories.
Thus the suitability of particular sampling method is deduced from what information is considered important.
A recent work of Vrotsou et al.~\cite{Vrotsou2015} introduce a systematic stepwise methodology for trajectory simplification with emphasis on visual analysis.
Even though they primarily developed the tool to analyze three dimensional trajectories, it is not limited to them only.

In the field of molecular biology as well as systems biology, there are several examples of methods focusing on trajectory analysis.
Bidmon et al.~\cite{bidmon2008} present an abstract way of identification and visualization of solvent molecules' pathways within molecular dynamics. 
In comparison to previous solutions, their approach preserves valuable information on the directions and velocities of water molecules routing along these paths. 
Another approach that describes a guidance through a complex simulation trajectories in systems biology is presented by Luboschik et al.~\cite{Luboschik2012}. 
The method addresses biochemical reaction networks and aims to provide the users with a tool for investigating the overall behavior of a modeled system and detailed behavior at the same time.

\subsection{Visualization of Cavity and Tunnel Features}
Phillips et al.~\cite{phillips2010} propose a method to quantitatively estimate molecular features, e.g., volume and surface areas, via ray-casting technique. This involves computation of cavities.
Lindow et al.~\cite{LindowBH11} introduce a technique that allows to extract significant paths from the molecules. 
In their approach the authors utilize Voronoi diagram of spheres. 
Their final visualization is achieved by means of placing light sources on the extracted paths to enhance the presence of tunnels.
Parulek et al.~\cite{parulek2012} exploit scatterplots to communicate the evolution of protein voids. 
In their later study~\cite{parulek2013} they also suggest to utilize amino acids physico-chemical properties related to cavities to help users to navigate through their occurrences. 
The visualization if then achieved in the focus and context manner.
Lindow et al. \cite{Lindow2013} present an approach for visualization of temporal evolution of cavities in a temporal graph, which, to a certain extent, resembles our temporal tunnel model. 
In this work they focus on the interactive exploration of the dynamics of protein cavities that can form the transportation path for a ligand. 
They calculate and visualize the cavity volume and analyze the time-dependent changes of the cavity structure.
The cavity dynamics is captured by rendering the cavities in a single image. 
The final visualization is achieved through the molecular surface representation colored according to time. 
Krone et al.~\cite{krone2013features} present a similar approach, where they extract and track tunnels in MD simulations. They exploit temporal graphs to communicate the evolution of surface areas of tunnels. In our technique, we go one step further, where in addition, we incorporate the ligand-protein interaction information and provide users with the means to navigate through details of this interaction. Moreover, we analyze sequences of several thousands of frames, which is not the case in aforementioned approaches.
Kozlikova et al.~\cite{kozlikova2014vcbm} propose a way to seamlessly visualize the geometry and shape of tunnels across MD simulation. Here, they aim at 3D visualization solely, which is not suitable way of exploring and understanding of thousands of simulation time-steps.
Byska et al.~\cite{byska2016} introduce an approach to interactively explore the tunnel objects in MD simulations. Similarly to our approach they visualize the time-varying tunnel as a profile graph that includes information on surrounding amino acids. Nevertheless, they focus on a single tunnel instance and do not provide the means to explore the ligand-protein interaction.

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

In protein engineering, all these effort can finally lead to the detection of amino acids along the ligand trajectory which caused problems, i.e., were the key players in situations when the ligand gets stuck.
Such amino acids are then the best candidates for subsequent mutation of the protein chain when these amino acids are replaced by more suitable ones wrt. their size and properties.
On the other hand, in drug design the aim is to propose modifications of the ligand to increase the binding likelihood in order to design a better drug produced from this ligand.

The input data is obtained from the simulations of molecular dynamics which contains the movements of the protein and one or more ligands.
Ligands can follow two main routes -- they can be transported from the outside environment to the protein active site or vice versa (after the desired reaction the product leaves the protein).

The length of the simulations may vary from few hundreds to hundreds of thousands of time steps.  
This depends namely on the ligand velocity and its ability to find the proper path to the active site.
Figure \ref{fig:lig_movement} shows an example of a ligand trajectory consisting of $10.000$ time steps. 

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/lig_movement.png}
  \caption{\label{fig:lig_movement} Ligand trajectory for a simulation containing $10.000$ time steps. TODO change image, add molecule}
\end{figure}

Long simulations can often contain many time steps when the ligand followed an impasse -- it tried to find the proper entrance point to the protein (tunnel gorge) or entered a wrong tunnel and had to return.
Such parts of the simulation could be of less interest so that the user should be provided with a possibility to filter them out and focus only on the interesting parts.

%-------------------------------------------------------------------------
%\section{Design and Implementation}
\section{Visualization Design}
In this section we describe the design rationale of our visualization approach to interactively explore the ligand trajectory described above.
The design is tightly related to the following problems posed by the biochemists:
\begin{itemize}
\item Due to the immerse length of the simulations, it is almost impossible to easily separate and navigate through simulation parts given by the ligand position, i.e., whether it is outside the protein, inside a wrong or correct tunnel.
\item The scattered nature of the ligand motion makes it hard to follow the overall ligand direction.
\item There is no quick and straightforward way to explore the relation between physico-chemical properties of the protein tunnel and its geometry to assess the ligand bottleneck.
\end{itemize}

To tackle the aforementioned challenges, we propose a multiscale visualization system (Fig.~\ref{fig:teaser}), which enables visual information-seeking~\cite{shneiderman1996} in protein-ligand interaction simulations. 
The main idea is to provide meaningful information at each data abstraction level that is given by the current temporal selection, i.e., the user defined temporal window.
On the highest level, we classify ligand motion into two basic categories: outside the molecular surface (represented as solvent excluded surface~\cite{Richards}) and inside the protein (Fig.~\ref{fig:teaser}-0). 
The latter one is divided into two sub-cases. 
In the first case the ligand enters a tunnel but there is an obstacle preventing it to get to the active site and the ligand is expelled from the inner space back to the outer environment.
In the second case the ligand reaches the active site. 
Further, the visualization highlights the most prominent motion patterns that reflect the amount of movement the ligand made towards to or away from the active site. 
This information is acquired by means of a block-wise aggregation scheme of the ligand trajectory performed automatically.
Here we obtain a list of $m$ sequential temporal blocks, $B=\{b_1,\ldots,b_m\}$ (Fig.~\ref{fig:teaser}-1). It is important to mention that the blocks are non-overlapping in time meaning that if $b_i=[t_{100},t_{110}]$ then $b_{i+1}=[t_{111},...]$. For simplicity of explanation we define each temporal block as interval $b_i=[t_a,t_b]$ and the corresponding positions of ligands at time steps $t_a$ and $t_b$ as $P(a)$ and $P(b)$.
We propose four different aggregation strategies, where each one suits particular needs of domain specialists. Note that the aggregation schemes can be easily extended based on the application requirements.
Parallel to set $B$ we form a simplified representation of the ligand trajectory, which we refer to as \textit{temporal tunnel}.
Control points of the temporal tunnel are represented by ligand positions at the last time-step of each temporal block $b_i$ (Fig.~\ref{fig:teaser}-2).
We denote the last time step of $b_i$ as $E(i)$. In this manner, we extract a set of time steps $E_B=\{E(1),\ldots ,E(m)\}$ representing $m$ temporal blocks of a trajectory simplification that reflects the set $B$.

Each temporal block, as well as the corresponding segment within the temporal tunnel, is then described by several features representing the ligand motion, the empty space around the ligand (Fig.~\ref{fig:teaser}-3a), and physico-chemical properties during the time the ligand spent inside $b_i$ (Fig.~\ref{fig:teaser}-3b).

%\begin{figure}[ht!]
%	%\centering
 % \includegraphics[width=1\linewidth]{img/teaser.pdf}
 % \caption{\label{fig:overview} }
%\end{figure}

%The first problem is addressed by the simple visualization on the top of the window.
%Its goal is to provide the users with the general overview of the whole simulation and highlight individual parts of the ligand movement.
%In general, we can classify ligand motion into three basic categories, which are represented in the following way.
%In each time step we check the position of the ligand with respect to the protein solvent excluded surface. 
%Whenever the ligand passes through the surface, we store the corresponding time step and ligand position.
%If the ligand is outside the protein surface, it means that it still tries to find the entrance point to enter the protein through a tunnel gorge on the surface. 
%When the ligand enters the protein inner space, we can distinguish between two cases.
%Very similar solution can be adopted for the opposite direction when the ligand aims to leave the active site and reach the outer solvent.

%As a result, we obtain three different types of movements which are highlighted in the overview representation (Fig. \ref{fig:overview} a)).
%Yellow parts represent the ligand movements outside the molecule, red parts show the parts where the ligand entered a wrong tunnel and had to return, and green parts depict the situation where the ligand finally took the correct tunnel and reached the active site.
%The user can interactively select an arbitrary part and the remaining parts of our proposed solution (Fig.~\ref{fig:overview} b)) are interactively updated in order to present only the information for a selected part.
%So the biochemists are easily navigated to a selected time span they want to explore in more detail.
%
%\begin{figure*}[htb]
	%\centering
  %\includegraphics[width=1\linewidth]{img/overview.png}
  %\caption{\label{fig:overview} Illustration of our proposed technique. Section a) gives an overview of the individual parts of the simulation (yellow = ligand is outside the protein, red = ligand entered a wrong tunnel, green = ligand entered a correct tunnel and reached the active site). Section b) shows the detailed information about a selected part. TODO}
%\end{figure*}

%Even though the detected parts are usually much shorter in comparison with the length of the original simulation, it is still nearly impossible to comprehend the ligand movement. 
%This is caused by ligand jittering which makes the perception of the significant ligand movements very hard to follow.
%This is clearly visible in Figure~\ref{fig:temporal} a)) which shows the whole ligand trajectory in case when the ligand entered the solvent excluded surface and entered the active site.
%The same holds true for cases when the user is watching the animated motion of the ligand. 
%Hence we suggest the solution based on a multi-scale simplification model which introduces the concept of so called \textit{temporal tunnel}.  

\subsection{Temporal Tunnel Features}
Each temporal block and the respective temporal tunnel segment is associated with several features computed interactively.

We provide the information that represents the amount of free space around the ligand when leaving one temporal block and subsequently entering the next one.
At each exit point $P(b)$, we retrieve the $N$ closest atoms to the ligand, which in our case is set to $N=10$. Then we compute the center of mass $C$ of these atoms and a distance $r$ from this center to the closest atom. 
This forms a sphere $(C_b,r_b)$ representing the extent of the free space around the ligand at $P(b)$. 
The list of radii is then exploited to form the graph (Fig.~\ref{fig:teaser}-3a), which provides the information about the amount of free space around the ligand when leaving the current block. 
This represents a crucial information when studying the relation between the geometric and physico-chemical bottlenecks.

The information about the surrounding acids is also very crucial when exploring the ligand bottlenecks. 
For each time step within the temporal block we compute the three closest amino acids from the ligand. 
These are then grouped to form a list of amino acids representing the entire block. 
We provide the visual representation of this list (Fig.~\ref{fig:aacids}), where each amino acid defines one line in the list. 
The line is colored with respect to a selected physico-chemical property~---~our representation supports switching between hydrophobicity, partial charges, and donors and acceptors.
The interruption in some of these lines is caused by the fact that the given amino acid is not present around the ligand in the corresponding temporal block.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/aacids.png}
  \caption{\label{fig:aacids} Representation of amino acids surrounding the temporal tunnel and their physico-chemical properties. Coloring corresponds to a selected property, the line interruption means that this amino acid was not detected around the ligand in the corresponding temporal block.}
\end{figure}

Another feature that we assign to a block is represented by two values related to the distance the ligand takes when crossing the block. 
First, the total distance the ligand passed through between the neighboring time steps of the temporal block, is defined as $\sum_i |P(t_i),P(t_{i+1})|$.
Secondly, a relative distance the ligand passed between the first and the last time step of the temporal block with respect to the position of the active site $O$, is detected as $|P(a),O|-|P(b),O|$. The total distance is mapped onto the height of the bar while the relative distance is conveyed via the color (Fig.~\ref{fig:bars}). 
Here, yellow color represents the direction towards the active site, while red color means that the ligand moved in the opposite direction.
\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/bars.png}
  \caption{\label{fig:bars} Coloring scheme used for individual bars which encodes the direction of the ligand with respect to the active site position. Yellow color corresponds to the motion towards the active site, orange color corresponds to the opposite direction.}
\end{figure}

The abstracted visualization, integrating the computed features, is interactively linked with the 3D view where the temporal tunnel is represented as a system of linked tubes.
We color code the tubes by time or by the relative distance value.
The main advantage of this representation is its complementarity with respect to the spatial orientation which is not provided in the bar chart (Fig.~\ref{fig:teaser}-2).

%
%\begin{figure}[htb]
	%\centering
  %\includegraphics[width=1\linewidth]{img/temporal.png}
  %\caption{\label{fig:temporal} Left: selected part of the whole trajectory when the ligand enters the active site. Right: visualization of the corresponding temporal tunnel. TODO change images!}
%\end{figure}

\subsection{Trajectory Simplification}
In order to reveal significant ligand motion patterns, we introduce a hierarchical simplification model that, in addition, allows us to emphasize several important aspects related to the mutual protein-ligand interaction. 
In more detail, at each level our visualization provides i) the main direction of the ligand motion, ii) the sections of the simulation where the ligand gets stuck and iii) the geometrical and physico-chemical properties on sites where the ligand gets stuck. 

As already mentioned, the main source of the visual clutter (Fig. \ref{fig:temporal}) is the ligand motion itself, which resembles the random Brownian motion. Here, the removal of this jittery motion would allow us to reveal more dominant ligand motion patterns. 
Nevertheless, this also means to approximate the initial trajectory, which on the other hand is a trade-off for providing a good overview of entire ligand motion instead.
As a standard solution, to reduce this jittering and also to simplify the trajectory, the Hermite (or similar) interpolation technique can be used. 
However, such an interpolation simplification would still not suffice since the spatial distance between two neighboring time steps is usually very small, thus the interpolation scheme still contains a lot of jitter (Fig.~\ref{fig:temporal}). 
\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/temporal.png}
  \caption{\label{fig:temporal} A cut trajectory section shows the ligand entering the active site. The trajectory is obtained using Hermite interpolation, which still contains a lot of jittery motion.}
\end{figure}
For completeness, we also tested the Ramer~-~Douglas~-~Peucker algorithm. 
It reduces the number of points in a curve by starting from the line segment between the first and last point of the trajectory. 
For each segment it adds a point from the original trajectory which is the furthest one from this segment.
This process is repeated until the desired resolution of the trajectory is reached.
In case of ligand trajectory, this method keeps only the extreme points on the trajectory, which unfortunately has no significant meaning from the biochemical point of view.
Therefore, we propose a solution that sub-sample the original trajectory and aggregate the protein-ligand interaction in a distinct manner. 
The intention is that the user can interactively switch between different aggregation strategies while the result is visualized instantly.
In all proposed solutions we employ the position of the active site that can be either user defined or obtained directly from the simulation, e.g., as the final position of the ligand.

%Except for a lot of jitter, the trajectory often contains sequences that form the so-called \textit{loops}.
%The loop is thought of as a portion of the trajectory in which the ligand got stuck in a given position $p$ (time step $t_i$), then follows an alternative route, i.e., not heading towards the active site, and finally returns to a position $q$ lying close to $p$ where it got stuck (in time step $t_j$). We define this condition as follows:
%\begin{equation}
%|p,q| < d,
%\label{eq:loop}
%\end{equation}
%where $d$ is a given distance threshold defining the similarity between two ligand positions (experimentally set to {\color{red}TODO}), and $t_i \neq t_j$, $i << j$. 

%\subsubsection{Simplification of the path}


\subsubsection{Zero-Crossings}
%{\color{red}(The automatic active site detection is currently supported only for input data in which the ligand is in the active site by the end of the simulation.)}.
% I guess it could be done for reentry simulation as well using the most distant place from entery point. But here we face the problem how to evalueate whether the ligand go stuck and lefet before actually reaching the active site (ever).  
This method is based on the assumption that in each time step $i$ the distance $d_i$ from the active site to the ligand center of mass can be evaluated, i.e., we define a set of distances $D=\{d_1,d_2, \ldots, d_n\}$ where $n$ is the number of time steps in the scrutinized part of the simulation. 
%We define ligand trajectory as a set $T = {t_i : 0 < i <=n}$ 
By means of this distance, one can easily detect time steps when the ligand changes its motion with respect to the active site, i.e., towards to or away from the active site. Using $d$ notation we represent these time steps as follows:
\begin{equation}
Z=\{t_i:\Delta d_i\cdot \Delta d_{i+1} <0\}. 
\label{eq:zc}
\end{equation}
The method operates with the concept of zero-crossing meaning either that the ligand heading towards the active site changed its direction and traveled back to the outer solvent or vice versa. 
A single pair of zero-crossings then defines the so-called \textit{loop}. 
The important aspect is that the occurrence of loops corresponds to the locations when the ligand gets stuck. 
In a case that two zero-crossings having a larger temporal gap in between, i.e., $|t_i - t_{i+1}|>1$ and $\{t_i,t_{i+1}\}\in Z$, it reflects the fact that the ligand gets stuck somewhere between these two time steps.
When referring to each entry of $Z$ as a zero-crossing, we aggregate the user-defined amount $k$ of zero-crossings to form a temporal block $b_j$ such that $|b_j|=k$, i.e., when $k=2$ and $|Z|=20$, we acquire $10$ temporal blocks. 

%For the given parameter $k$, we denote the last time step of this temporal block as $E_k(j)=\{t_{j_k}:T_{B_j}=\{t_{j_1},\ldots,t_{j_k}\}\}$. 
%In this manner, we extract a set of time steps $E_k=\{E_k(1),\ldots ,E_k(m)\}$ representing $m$ temporal blocks of a trajectory simplification that reflects the $k$~parameter. 
%It is important to mention that the corresponding temporal tunnel is formed by ligand positions in $E_k$ solely. 

%Now, for a given 

%For instance, on the top-most level, the temporal tunnel contains no loops neither.
%The multi-scale model of the temporal tunnel is then built where on the highest level all loops are omitted.
%In other words, the top-level temporal tunnel contains only the time steps when the ligand headed towards the active site.
%The intermediate levels start to contain a certain number of loops with respect to the following rule.

Each block $b_j$ represents an interval in which the ligand has to make a given number of loops before a new block is created. 
Note that the last block could potentially contain a smaller number of zero-crossings.
As a consequence, if the ligand moves constantly in the same direction, it takes more time steps to accumulate before $k$ number of zero-crossings is reached. Therefore, the number of time steps in each block reveals either the parts of the trajectory where the ligand moves mostly in a single direction or the sections where it got stuck and thus is unable to continue towards the active site. 
Nevertheless, this information needs to be combined with the overall distance the ligand crossed within the block to avoid the misinterpretation of longer loops. Additionally, the user has the possibility to alter parameter $k$ to adjust the granularity of block decomposition. 
Figure~\ref{fig:loops} demonstrates different results for altering the $k$ value.
%Even though this multi-scale model enables to switch between individual levels by increasing (or decreasing) the number of loops in cluster by one, we suggest that the current value should be multiplied (or divided) by a natural number. 
%This way clusters will be merged or divided uniformly, e.g, if the current number of loops in cluster is multiplied by two the two adjacent cluster will be merge into the single one and vice versa.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/zero_degradation.pdf}
  \caption{\label{fig:loops} Example of resulting trajectories for different values of the parameter $k$ which influences the granularity of block decomposition.}
\end{figure}

This type of trajectory simplification is beneficial mainly because it prevents the main bottlenecks of the temporal tunnel which are the most interesting and important sites of the simulation.
These sites where the ligand gets stuck for a significant portion of time correspond to parts of the trajectory which is worthwhile to explore in more detail and find out the reason why the ligand was not able to pass through the tunnel. 

\subsubsection{Uniform Sampling}
Here, we uniformly divide the whole simulation into a given number of temporal blocks. 
Each temporal block is of a fixed length given by the user-defined granularity of time represented by the size of the temporal span, i.e., $|b_i|=l$, where $l$ represents the given number of time steps per temporal block. 
The value represented in this aggregate is the number of zero-crossings in this time interval. 
This can be seen as an orthogonal simplification strategy in comparison with the aforementioned one.

Such a model helps to evaluate to which extent the ligand was stuck for a given amount of time.
The advantage of this approach is its uniformity that allows users to easily perceive the transition between different temporal selections.
Moreover, this concept is commonly used by the biochemists in cases when they deal with a large amount of data or information, such as in computation of protein cavities and tunnels. 
Here the user chooses a sampling step at which the cavities are computed. 
This gives the user the rough idea of the presence of cavities within the whole simulation.
%Nevertheless, the given granularity can cause that important time steps with respect to the ligand motion will be skipped. 

Figure~\ref{fig:uniform} shows an example of uniform simplification results on different levels. 

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/uniform_degradation.pdf}
  \caption{\label{fig:uniform} Example of uniformly sampled trajectories for different values of the parameter $l$ which influences the granularity of block decomposition (number of samples in each level).}
\end{figure}


\subsubsection{Amino Acids}
%{\color{red}TODO BK leave it here?}
The geometric properties of the temporal tunnel are important characteristics mainly due to the ability to reveal the geometric bottlenecks.
However, the physico-chemical properties of the amino acids surrounding the ligand trajectory are similarly important.
For instance, when the mutual properties of the ligand and the amino acids are not compatible, it can prevent the ligand to pass through even when the tunnel is wide enough. 
Therefore, we utilize the information contained within the amino acids and aggregate all the ligand positions into a single temporal block when being surrounded by the given selection of amino acids.
We aggregate the ligand positions where the ligand was surrounded by the same set of amino acids. In our study, we extract the three closest amino acids from the ligand.
The provided interactivity allows users to change the number of allowed differences in the surrounding amino acids to belong to the same block. 
%{\color{red} Note that these levels are limited to three since for each time step we compute only three closest amino acids.}.
Figure~\ref{fig:aa} shows examples of the resulting trajectories with the increasing level of differences.

%As a result, on the lowest level the model aggregates only the smallest loops located in the same area. 
%While all the loops (longer or shorter) on the border between two ligand positions surrounded by different amino acids and hence different properties are preserved.  
%This applies also for higher levels, however, the change there would have to be more significant.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/residue_degradation.pdf}
  \caption{\label{fig:aa} Example of trajectories sampled according to the changes in the surrounding amino acids.}
\end{figure}

Such model allows us to estimate the time ligand spent stuck with respect to the given set of amino acids. 
Moreover, it indirectly provides users with the hints of amino acids which caused the ligand being stuck and thus should be potentially replaced, i.e., mutated.


\subsubsection{Loop Degradation}
This method is based on a user-defined variable $V$ that specifies the maximum allowed distance between the entry and exit points of each block $b_i=[t_a,t_b]$:
\begin{equation}
b_i = \{t_j : a \leq j \leq b \land |P(a), P(b)| < V \},
\label{eq:ld}
\end{equation}
where $P(a)$ and $P(b)$ denote ligand positions at time steps $t_a$ and $t_b$ respectively. Figure~\ref{fig:ld} shows the results for several different values of $V$.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/loop_degradation.pdf}
  \caption{\label{fig:ld} Example of trajectory simplification using the loop degradation approach.  }
\end{figure}

The main idea in this method is to remove those parts of the trajectory where the ligand moves only slightly while neglecting the jittery movements that are within the radius of $V$. 
Therefore, the method allows us to showcase the dominant ligand direction.



%\subsection{Temporal Tunnel Compound Views} \label{visualization}
%Each simplification scheme provides a detailed information aggregated within the acquired temporal blocks, which asks for a meaningful visual representation. Therefore, we propose a compound visualization system (Fig.~\ref{fig:overview}b) composed of dedicated charts representing information provided by the corresponding temporal tunnel. 
%This information should assist users to quickly explore interesting sites on the ligand trajectory.
%Our compound view is divided into three parts.
%
%The top part shows the bar chart that captures the aggregated information about individual blocks obtained via the user-selected simplification method.
%Each temporal block is represented by a single bar and its height corresponds to the actual aggregated value, i.e., either the number of zero-crossings or the number of time steps. 
%In other words, such a combination provides the users with the possibility to explore the correspondence between the geometrical bottlenecks and parts the ligand got stuck.
%These parts form another type of bottlenecks -- those defined by the physico-chemical properties of the surrounding amino acids. 
%In general, the geometric and phys-chem bottlenecks are considered as equal. 
%Nevertheless, a case that the tunnel is relatively wide enough and yet the ligand gets stuck reflects the situation when the properties of the ligand are not compatible with the properties of the amino acids interacting with the ligand.
%
%To explore both types of bottlenecks and their corresponding amino acids in more detail, we propose the third part of the proposed visualization (Fig.~\ref{fig:aacids}).


%-------------------------------------------------------------------------
\section{Results and Discussion} \label{discussion}
The proposed techniques were tested on several ligand trajectories with different scenarios: i) the ligand traveled from the outer solvent to the active site, ii) the ligand left the active site as well as the molecule and iii) the ligand entered the active site, then left and reentered the site again.
The length of the tested trajectories spanned from $50.000$ to $100.000$ time steps.
Here we describe the integration of our approach to the traditional workflow of biochemists and the contribution of this new approach.
When exploring the molecular dynamics simulation capturing the ligand motion, the biochemists traditionally observe the ligand animation using some of the widely used molecular visualization tools.
Additionally, they often plot line charts showing different properties, such as geometric bottlenecks along the ligand path. 
The exploration process is iterative so the users are manually selecting interesting parts of the trajectory according to the information extracted from the plotted graphs. 
These parts are then again plotted.
This process is repeated and under the best of conditions it helps to reveal the interesting amino acids around the bottlenecks of the trajectory.
These amino acids are then the best candidates for protein mutations serving for a given purpose, e.g., removing the bottleneck or closing this path completely. 
This process is usually very lengthy and requires a lot of effort from the user.

%Our proposed tool removes the main limitations of the traditional approach.
The proposed visualization assists the biochemists to immediately distinguish between individual parts of the trajectory -- when ligand was inside and traveled from or towards the active site, or it was outside the molecule. Then, by selecting a time interval of interests, the user is automatically navigated to the corresponding time sequence.
%It demonstrates how the biochemists can interact with the tool and how it helps them to understand the ligand trajectory much faster and in more comprehensible way than before.

In order to show the process of exploration of the selected part in more detail, we describe a case performed on the real data obtained from the biochemists.
The scrutinized trajectory first captures the ligand movement outside the protein and then its transportation to the active site.
Our visualization automatically distinguishes between these two states and divides the trajectory to two parts (Fig.~\ref{fig:case}).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/case.png}
  \caption{\label{fig:case} Overview of the whole trajectory. First part (white) defines the part where the ligand was outside the molecule. Yellow part highlights the part where the ligand entered the molecule and headed towards the active site.}
\end{figure}

The user can select the part of the trajectory when the ligand entered the molecule and aimed to get to the active site.
As the original trajectory is very scattered (Fig.~\ref{fig:cross} a)), the user exploits one of the simplification methods to see the significant motions of the ligand.
When using the simplification based on zero-crossings, the user should be able to distinguish between parts where the ligand gets stuck and parts where its progress towards the active site was substantial (Fig.~\ref{fig:cross} b)).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/cross.png}
  \caption{\label{fig:cross} a) original trajectory of the ligand inside the molecule, b) simplification based on zero-crossings revealing three different parts.}
\end{figure}

This information is easily readable from the bar chart accumulating the information about the ligand progress (Fig.~\ref{fig:casebar} top).
The highest bar shows the part of the trajectory when the ligand did not change its direction.
The yellow color indicates that the ligand traveled towards the active site. 
This bar further divides the trajectory to three parts which can be further explored by interactive selection of their corresponding bars (Fig.~\ref{fig:casebar} bottom).
\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/casebar.png}
  \caption{\label{fig:casebar} Bars showing the aggregated temporal blocks. a) The highest yellow block defines the part where the ligand traveled directly towards the active site. b) Example of interactive selection of bars.}
\end{figure}

Then the user can focus on details of this part of the trajectory by decreasing the level of simplification until it reaches the level of raw data where all original time steps of this part are displayed. At this level we can easily detect the bottleneck from the visualization part showing the radii of empty sphere around in each ligand position (Fig.~\ref{fig:radius}). The bottom part of the visualization shows the amino acids in the closest neighborhood for each ligand position.
So the user can easily explore the amino acids forming the bottleneck and by selecting them, they are automatically highlighted in the 3D visualization.

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/radius.png}
  \caption{\label{fig:radius} Curve representing the radius of the empty sphere around the ligand helps to determine the geometrical bottleneck. The amino acids surrounding the bottleneck are listed below and can be interactively selected.}
\end{figure}

In all levels, the trajectory in the context of the 3D representation of the molecule can be observed as a tube which gives the user the idea of the spatial orientation of the trajectory with respect to the protein.
When hovering over individual bars, the corresponding part of the tube is highlighted (Fig.~\ref{fig:tube} a, the orange section).
By selecting the amino acids surrounding the trajectory the user can observe the interacting atoms from the ligand and the amino acids (Fig.~\ref{fig:tube} b).

\begin{figure}[htb]
	\centering
  \includegraphics[width=1\linewidth]{img/tube.png}
  \caption{\label{fig:tube} a) The trajectory can be visualized as a tube. The highlighted section corresponds to one selected bar. b) The ligand (red) can be added and its surrounding amino acids (yellow) can be highlighted.}
\end{figure}

The same workflow can be followed by using the other simplification methods as well.
We tested these methods on the same trajectory.
Each of them detects several interesting spots on the trajectory which gives the biochemist a hint to an interesting spot for further exploration.

The uniform sampling method nicely showed the progress of the ligand along the trajectory.
On the higher levels it helps to reveal the overall progress of the ligand divided into uniform blocks. 
This method clearly shows that at the end of the trajectory the ligand travels around the active site for a significant portion of time (traveling forward and backward) before it finally reaches the active site.

The loop degradation method guided the user to the second half of the trajectory. 
Here the method detects three interesting blocks in which the ligand follows a loop in a backward direction. 
The neigborhood of one of these bars was rather flat which says that the ligand movement before and after this block was rather smooth (without significant loops).
Detailed exploration of this bar reveals that at the beginning of the loop the radius is small and prevents the ligand to proceed towards the active site.

The aggregation with respect to the physico-chemical properties of the surrounding amino acids is the most sophisticated method from the biochemical point of view because it incorporates a non-trivial parameter.
Therefore, also its interpretation can be more complicated.
In this particular case the method shows that in the first part of the trajectory the ligand is surrounded by very similar amino acids and when begins to move faster towards the active site, the amino acids (so the physico-chemical properties of the trajectory) change significantly as well.

%Naturally, it is worthwhile to combine these methods in order to reveal interesting spots in the trajectory taken from different points of view. 
%This combination can be based on changing the methods withing the exploration or the user can perform the exploration individually and then compare the results.
%Some of the spots detected by our proposed methods can overlap which can even strengthen their importance.

\section{Conclusion}
In this paper we proposed a method for intuitive and interactive exploration of ligand trajectory when interacting with a protein molecule.
As the original trajectory is very jittered, we proposed four methods for trajectory simplification which aim at describe and analyze the substantial ligand motion with respect to different criteria.
Each of them helps to reveal interesting portions of the trajectory, which can be further explored by the interaction with our proposed visualization.
The visualization consists of several parts conveying the information about the aggregation of time steps, the radius of the temporal tunnel, and different properties of the amino acids surrounding the temporal tunnel and thus interacting with the ligand.
The simplification methods were tested on several cases and one of them was demonstrated, along with the discussion about their contributions.

In the future it could be interesting to find a way to combine or link the proposed methods to a single one so the user will not be forced to switch between them manually.
Moreover, it would be interesting to compare the temporal tunnel with tunnels computed by one of the existing geometric approaches, e.g., using CAVER or MOLE.

%-------------------------------------------------------------------------

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha}

\bibliography{refs}

\end{document}
