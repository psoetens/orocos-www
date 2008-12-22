<?xml version="1.0" encoding="UTF-8"?>

<!--
	When an XML doc is converted, it is presented to the viewer out of context.
	If the context was important (eg it was XHTML comprising a hrefs and img srcs)
	that must be repaired. 
	Using the HTML base markup is ugly. instead we'll use it as a parameter to all links.
	
	If href_base parameter is set, then all hrefs, img src etc in the document
	need to be adjusted to point back to the real data source location.
	This will have to be applied by clever re-writing
	of the links, as this template attempts.
	
	When importing or otherwise moving a site or subsite around, it may be appropriate
	to place the images, css and other 'resources' in a different place from the html content.
	This is the src_base parameter.

	When seriously renovating a site from one system to another, we may be changing or
	even discarding the suffix. If so, set replace_suffix to true, and tell me the new suffix.
	replace_suffix = TRUE and new_suffix = '' means discard suffixes altogether (just hrefs, not srcs)

	$Id: rewrite_href_and_src.xsl,v 1.7.2.1 2007/02/20 12:30:40 dman Exp $
-->


<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	xmlns:xhtml="http://www.w3.org/1999/xhtml"
	xmlns="http://www.w3.org/1999/xhtml"
>
<!--
	output must be set to be XML compliant, else the meta and link tags
	(unclosed singletons in old HTML) will not validate on the next pass.
-->
	<xsl:output method="xml" encoding="UTF-8" />

	<xsl:param name="href_base">thebase</xsl:param>
	<xsl:param name="src_base">thesrc</xsl:param>

	<xsl:param name="replace_suffix"></xsl:param>
	<xsl:param name="new_suffix">.newhtm</xsl:param>

 <xsl:param name="strip_script_tags"></xsl:param>

<!--	
	<xsl:include href="safe_pass_through.xsl" />
PHP4 just breaks for some reason
 -->
	<!-- Include some intelligent identity transformations for the rest of the page -->
	
<!-- 
	rewrite everything that uses 'href' 
-->
   <xsl:template name="rewritehrefs" match="node()[@href]">
	<!--
   	rewrite <xsl:value-of select="@href" /> using <xsl:value-of select="$href_base" />
	-->
		<xsl:call-template name="rewritelink">
			<xsl:with-param name="attname">href</xsl:with-param>
			<!--
				Problem - hrefs that link directly to resources (eg, the big jpeg) need extra care.
				Looking for the suffix is not great, but it's a best guess.
				Should use ends-with, but sablotron doesn't play that.
				This needs work and may cause problems.
			-->
			<xsl:with-param name="linkbase">
				<xsl:choose>
					<xsl:when test="contains(@href,'.htm') or contains(@href,'.php') or contains(@href,'.asp') or contains(@href,'.jsp') ">
							<xsl:value-of select="$href_base" />
					</xsl:when>
					<xsl:when test="(substring(@href, string-length(@href) ) = '/' ) or not( contains(@href,'.'))">
						<!-- aka ends-with('/') --> 
						<xsl:value-of select="$href_base" />
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="$src_base" />
					</xsl:otherwise>
				</xsl:choose>
			</xsl:with-param>

			<xsl:with-param name="replace_suffix">
				<xsl:choose>
					<xsl:when test="contains(@href,'.htm') or contains(@href,'.php') or contains(@href,'.asp') or contains(@href,'.jsp') ">
						<!-- only these instances get suffix replaced -->
						<xsl:value-of select="$replace_suffix" />
					</xsl:when>
				</xsl:choose>
			</xsl:with-param>

		</xsl:call-template>
   </xsl:template>


<!-- 
	rewrite everything that uses 'src'
 -->
   <xsl:template name="rewritesrcs" match="node()[@src]">
		<xsl:call-template name="rewritelink">
			<xsl:with-param name="attname">src</xsl:with-param>
			<xsl:with-param name="linkbase"><xsl:value-of select="$src_base" /></xsl:with-param>
		</xsl:call-template>
   </xsl:template>


   <xsl:template name="rewritebackgroundlinks" match="node()[@background]">
		<xsl:call-template name="rewritelink">
			<xsl:with-param name="attname">background</xsl:with-param>
			<xsl:with-param name="linkbase"><xsl:value-of select="$src_base" /></xsl:with-param>
		</xsl:call-template>
   </xsl:template>
 
 
   <xsl:template name="rewriteembeddedmedia" match="node()[@name='movie' and name()='param']">
    	<!--
    		SWF and things with <param name='movie' value='source/file.swf' /> syntax.
    		Awkward node()[name='node-name'] xpath is used here to ignore namespaces.
    	-->
		<xsl:call-template name="rewritelink">
			<xsl:with-param name="attname">value</xsl:with-param>
			<xsl:with-param name="linkbase"><xsl:value-of select="$src_base" /></xsl:with-param>
		</xsl:call-template>
   </xsl:template>



<!-- 
	rewrite everything that has a link (href,src, etc)
	to use a link relative to somewhere else
 -->
   <xsl:template name="rewritelink">
	   <xsl:param name="attname" />
	   <xsl:param name="linkbase" />
	   <xsl:param name="replace_suffix" />
	<xsl:copy>
		
		<xsl:for-each select="@*" >
			<xsl:choose>

				<xsl:when test="name()=$attname">
				
					<!-- these ARE the droids you are looking for -->
					<xsl:choose>

						<xsl:when test="not(contains(.,':')) and not(starts-with(.,'/')) and not(starts-with(.,'#'))">
					   <!-- 
					       It has no scheme, and is doesn't start with /
					       It's a partial Url, may need help being relative
					       Rewrite it
				        -->
							<xsl:attribute name="{$attname}">
							<xsl:value-of select="$linkbase" />

							<!-- Also, trim the suffix off this file and 
							     replace it on-the-fly, if asked to.
							    Cannot really handle query strings, hashes or anything
							-->
							<xsl:choose>
                <!-- testing against the input $replace_suffix flag parameter still returns TRUE if given '0'. Bool got cast into string somewhere  -->
								<xsl:when test="number($replace_suffix) and substring-before( . ,'.')">
								<!-- currently broken if path starts with (or contains?) "." -->
									<xsl:value-of select="substring-before( . ,'.')" /><xsl:value-of select="$new_suffix" />
								</xsl:when>
								<xsl:otherwise>
									<xsl:value-of select="." />
								</xsl:otherwise>
							</xsl:choose>

							</xsl:attribute>
				
						</xsl:when>
						<xsl:otherwise>
						<!-- 
							Full Url, it defines its own scheme, leave as is 
						-->
							<xsl:copy-of select="." />
							<xsl:apply-templates select=" * | text()"/>
						</xsl:otherwise>

					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>
					<!-- 
						It's one of the other attributes
						Copy all and carry on 
					-->
					<xsl:copy />
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
		<!-- 
		  done attributes, needs to carry on with the contents 
		-->
			<xsl:apply-templates />

		</xsl:copy>

   </xsl:template>
	     


<!-- Identity transformation template - let everything else pass through  -->
   <xsl:template match=" * | comment() | processing-instruction() | text()">
      <xsl:copy>
         <xsl:copy-of select="@*" />

         <xsl:apply-templates
         select=" * | comment() | processing-instruction() | text()" />
      </xsl:copy>
   </xsl:template>

   <xsl:template match="*[local-name()='script']">
<!-- 
 general-case for script pass-through is tricky.
 Note, this match is LESS specific than the one that matches all src-ed elements
 so a script src='' thing is NOT touched here, only inline code blocks.
 -->
     <xsl:if test="not(number($strip_script_tags))">
      <xsl:copy>
         <xsl:copy-of select="@*" />
         <!-- xsl:comment-->
         <xsl:text disable-output-escaping="yes"> // &lt;![CDATA[</xsl:text>
         <xsl:value-of select="text()" disable-output-escaping="yes" />
         <xsl:text disable-output-escaping="yes"> // ]]&gt; </xsl:text>
         <!-- /xsl:comment-->
       </xsl:copy>
      </xsl:if>
   </xsl:template>
   
   <!-- in a strange turn of events, an empty noscript tag stopped half a site from rendering -->
   <xsl:template match="*[local-name()='noscript']">
     <xsl:if test="*|text()">
      <!-- Only passthrough noscripts with some content worth showing -->
      <xsl:copy>
         <xsl:copy-of select="@*|*|text()" />
       </xsl:copy>
     </xsl:if>
   </xsl:template>
	
</xsl:stylesheet>