############################
##MPM Changed delta, Affy SADD states delta as 2e-20
pmcorrect.mas <- function (object, contrast.tau = 0.03, scale.tau = 10, delta = 2^(-20))
#function (object, contrast.tau = 0.03, scale.tau = 10, delta = 9.536743e-07) 
###########################
{
    all.pps.pm <- pm(object)
    all.pps.mm <- mm(object)
    diff <- log2(all.pps.pm) - log2(all.pps.mm)
    delta <- rep(delta, nrow(diff))
    for (i in 1:ncol(diff)) {
        sb <- tukey.biweight(diff[, i])
        pps.pm <- all.pps.pm[, i]
        pps.mm <- all.pps.mm[, i]
        pps.im <- pps.mm
        j <- (pps.mm >= pps.pm) & (sb > contrast.tau)
        pps.im[j] <- pps.pm[j]/2^sb
        j <- (pps.mm >= pps.pm) & (sb <= contrast.tau)
        pps.im[j] <- pps.pm[j]/2^(contrast.tau/(1 + (contrast.tau - 
            sb)/scale.tau))
	#########################
	#MPM SADD Need to substract the PM-IM, I think this is the culprit
	pm.corrected <- apply(cbind(pps.pm-pps.im, delta), 1, 
            max)
        #pm.corrected <- apply(cbind(pps.pm, pps.im, delta), 1, 
        #    max)
	##########################
        diff[, i] <- pm.corrected
    }
    return(diff)
}
