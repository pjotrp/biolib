# QtlMap represents a map of markers - ordered by chromosome and position

class QtlMap

  include Contract

  def initialize markers
    cs = {}
    markers.each do | m |
      c = m.chromosome, pos = m.position
      cs[c] = {} if cs[c] == nil
      cs[c][m.position] = m
    end
    @chrpos = {}
    cs.sort.each do | k,v |
      c = k[0]
      @chrpos[c] = [] if @chrpos[c] == nil
      chr = @chrpos[c]
      chr.push v[k[1]]
    end
  end

  def each_chromosome
    @chrpos.keys.sort.each { | name | yield name, @chrpos[name] }
  end

  def markers name=nil
    ms = []
    if name
      return @chrpos[name]
    end
    each_chromosome do | name, markers |
      ms += markers
    end
    ms
  end

  def positions name
    @chrpos[name].collect { | m | m.position }
  end

=begin

Here the R/qtl logic for creating a map.

Listeria chromosome one, map extend.

debug: map <- create.map(cross$geno[[i]]$map, step, temp.offend, stepwidth)

Browse[1]> map
    D10M44       D1M3     loc2.5       loc5     loc7.5      loc10    loc12.5 
 0.0000000  0.9967536  2.5000000  5.0000000  7.5000000 10.0000000 12.5000000 
     loc15    loc17.5      loc20    loc22.5      D1M75      loc25    loc27.5 
15.0000000 17.5000000 20.0000000 22.5000000 24.8477329 25.0000000 27.5000000 
     loc30    loc32.5      loc35    loc37.5      loc40     D1M215    loc42.5 
30.0000000 32.5000000 35.0000000 37.5000000 40.0000000 40.4136087 42.5000000 
     loc45    loc47.5     D1M309      loc50    loc52.5     D1M218      loc55 
45.0000000 47.5000000 49.9946793 50.0000000 52.5000000 52.8001989 55.0000000 
   loc57.5      loc60    loc62.5      loc65    loc67.5      loc70     D1M451 
57.5000000 60.0000000 62.5000000 65.0000000 67.5000000 70.0000000 70.1120380 
    D1M504    loc72.5      loc75    loc77.5      loc80     D1M113     D1M355 
70.8064156 72.5000000 75.0000000 77.5000000 80.0000000 80.6232356 81.3962314 
   loc82.5     D1M291      loc85    loc87.5      loc90    loc92.5     D1M209 
82.5000000 84.9347425 85.0000000 87.5000000 90.0000000 92.5000000 92.6839378 
    D1M155 
93.6434358 

=end

  # Return an expanded map with new fake markers at each step location. Unlike 
  # R/qtl version it does it for all chromosomes

  def expand step
    contract("Step larger than 0") { step > 0 }
    each_chromosome do | name, ms |
      contract("Only one marker!") { ms.size > 1 }
      min = ms.first.position
      max = ms.last.position
      ps = positions(name)
      (min..max).step(step) do | pos |
        if !ps.include?(pos)
          ms.push(QtlMarker.new('loc'+name+'.'+pos.to_s,name,pos,-1))
        end
      end
      
    # minloc <- min(map)
    # map <- map-minloc
    # if(step>0 && off.end == 0) {
    #   a <- seq(floor(min(map)),max(map),
    #            by = step)
    #   if(any(is.na(match(a, map)))) {
    #     a <- a[is.na(match(a,map))]
    #     names(a) <- paste("loc",a,sep="")
    #     return(sort(c(a,map))+minloc)
    #   }
    #   else return(map+minloc)


    end

    QtlMap.new(markers)
  end

=begin
Calculate recombination fractions

Browse[1]> mf
function (d) 
0.5 * (1 - exp(-d/50))

debug: rf <- mf(diff(map))
Browse[1]> rf
        D1M3       loc2.5         loc5       loc7.5        loc10      loc12.5 
9.868842e-03 1.480874e-02 2.438529e-02 2.438529e-02 2.438529e-02 2.438529e-02 
       loc15      loc17.5        loc20      loc22.5        D1M75        loc25 
2.438529e-02 2.438529e-02 2.438529e-02 2.438529e-02 2.293467e-02 1.520355e-03 
     loc27.5        loc30      loc32.5        loc35      loc37.5        loc40 
2.438529e-02 2.438529e-02 2.438529e-02 2.438529e-02 2.438529e-02 2.438529e-02 
      D1M215      loc42.5        loc45      loc47.5       D1M309        loc50 
4.119027e-03 2.043460e-02 2.438529e-02 2.438529e-02 2.433467e-02 5.320415e-05 
     loc52.5       D1M218        loc55      loc57.5        loc60      loc62.5 
2.438529e-02 2.992995e-03 2.152112e-02 2.438529e-02 2.438529e-02 2.438529e-02 
       loc65      loc67.5        loc70       D1M451       D1M504      loc72.5 
2.438529e-02 2.438529e-02 2.438529e-02 1.119126e-03 6.895783e-03 1.665223e-02 
       loc75      loc77.5        loc80       D1M113       D1M355      loc82.5 
2.438529e-02 2.438529e-02 2.438529e-02 6.193675e-03 7.670512e-03 1.091675e-02 
      D1M291        loc85      loc87.5        loc90      loc92.5       D1M209 
2.376413e-02 6.521493e-04 2.438529e-02 2.438529e-02 2.438529e-02 1.835999e-03 
      D1M155 
9.503503e-03 

=end

def recombination_fractions name
  ps = positions(name)
  ds = []
  ps.each_cons(2) { | a | ds.push a[1]-a[0] }
  ds.map { | d | 0.5 * (1 - Math::exp(-d/50)) }  # Haldane
end

=begin

sim.geno by R/qtl

Browse[1]> dim(newgen)
[1] 120  50

(note 50 markers on chromosome 1, 120 individuals used below)

Browse[1]> newgen[1:4,1:4]
     D10M44 D1M3 loc2.5 loc5
[1,]      3    3      0    0
[2,]      0    3      0    0
[3,]      0    2      0    0
[4,]      3    3      0    0


Browse[1]> z$draws[1:10]
 [1] 3 3 2 3 2 2 2 2 1 3

Browse[1]> length(z$draws[])
[1] 48000

Browse[1]> max(z$draws)
[1] 3
Browse[1]> min(z$draws)
[1] 1

> dim(gp$geno[[1]]$draws)
[1] 120  50   8

> length(gp$geno[[1]]$draws)
[1] 48000
> length(gp$geno[[2]]$draws)
[1] 40320
> length(gp$geno[[3]]$draws)
[1] 32640

=end

end
